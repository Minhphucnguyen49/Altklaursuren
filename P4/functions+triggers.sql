
/***#1***/ 
   
    --1--
    create or replace function getFreeSeats(varchar, date) returns integer as $freeSeats$ 
        declare
            connection_id varchar := $1;
            departure_date date := $2; 
            seats integer; 
        begin 
            SELECT p.SITZPLATZ_ INTO seats 
            FROM ABFLUG d 
            JOIN FLUGZEUG p ON p.LUFTFAHRZEUGKENNZEICHEN = d.LUFTFAHRZEUGKENNZEICHEN
            WHERE d.CONNECTIONID = connection_id 
            AND d.DATUM = departure_date;
            
            IF(seats IS NULL)
            THEN 
                RAISE NOTICE 'NO RECORD FOUND. CHECK IF DATE AND CONNECTION ID are valid';
            seats := 0;
            END IF;

        return seats;
        end; 
    $freeSeats$ LANGUAGE plpgsql;

    --2--
    create or replace function maintenance(VARCHAR(50)) returns void as $maintenance$
        declare
            new_plane varchar := $1;
            today date := current_date;--???
        begin
            if exists (SELECT * FROM flugzeug f WHERE f.registrationnumber = new_plane)
            then 
                INSERT INTO WARTUNG (LUFTFAHRZEUGKENNZEICHEN, DATUM, FLUGFREIGABE) VALUES 
                    (new_plane, today, false);
                RAISE NOTICE 'Plane % is currently being maintained', new_plane;
            else
                RAISE NOTICE 'Plane % does not exist', new_plane;
            end if; 
        end;
    $maintenance$ LANGUAGE plpgsql; 
    
    --3--
    create or replace view passagierListe AS 
        SELECT 
        p.VORNAME, p.NACHNAME, 
        b.PREIS, 
        b.CONNECTIONID, 
        b.DATUM AS buchung_datum,
        f.START AS start, 
        a.NAME AS startflughafen, 
        f.ZIEL AS ziel, 
        a2.NAME AS zielflughafen
            FROM PASSAGIER p
            
            JOIN BUCHUNG b ON p.KUNDENNUMMER = b.KUNDENNUMMER
            
            JOIN FLUGVERBINDUNG f ON f.CONNECTIONID = b.CONNECTIONID
            
            JOIN FLUGHAFEN a ON a.IATA_CODE = f.START
    
            JOIN FLUGHAFEN a2 ON a2.IATA_CODE = f.ZIEL;

/***#2***/ 

    --1--	
    create or replace function getDistance(varchar(3), varchar(3)) returns float as $distance$
	declare
		iata1 varchar(3) := $1;
		iata2 varchar(3) := $2;
		EARTHRADIUS float := 6371.0;
		start record;
		ziel record;
		result float;
		deltaBreiten float;
		deltaLangen float;
	begin 
		SELECT 
            radians(LANGENGRAD) AS langen, 
            radians(BREITENGRAD) AS breiten INTO start
            FROM flughafen where IATA_CODE = iata1;

		SELECT 
            radians(LANGENGRAD) AS langen, 
            radians(BREITENGRAD) AS breiten INTO ziel 
			FROM flughafen where IATA_CODE = iata2;

		deltaBreiten := (ziel.breiten - start.breiten) / 2.0;
		deltaLangen := (ziel.langen - start.langen) / 2.0;
		result := 2.0 * EARTHRADIUS * 
			asin
			(	
				sqrt
				(
					(sin(deltaBreiten) * sin(deltaBreiten)) 
                    + 
                    cos(start.breiten) * cos(ziel.breiten) * (sin(deltaLangen) * sin(deltaLangen))
				)
			);
		return result;
	end
	$distance$ language plpgsql;

/***#3***/
    --1--
    create or replace function freeSeat() returns trigger as $$
	declare
		freeSeats integer := getFreeSeats(NEW.CONNECTIONID, NEW.datum);
	begin
		if freeSeats == 0 then
			raise exception 'Dont have seats anymore';
		end if;
		return new;
	end
	$$ language plpgsql;

	create trigger checkFreeSeat before insert on BUCHUNG
	    for each row execute procedure freeSeat();
    
    --2--
    create or replace function distance(varchar(6)) returns float as $$
	declare 
		start varchar(3);
		ziel varchar(3);
		flugnummer varchar(6) := $1;
	begin
		select START, ZIEL into start, ziel 
        FROM FLUGVERBINDUNG where CONNECTIONID = flugnummer;
		return getDistance(start, ziel);
	end
	$$ language plpgsql;

	create or replace function getPassagierBonusmeilen(integer) returns integer as $$
	declare
		kundennummer integer := $1;
	begin
		return (select bonusmeilen from BUCHUNG where KUNDENNUMMER = kundennummer);
	end
	$$ language plpgsql;

	create or replace function payWithBonusmeilen() returns trigger as $payWithBonus$
	declare
		distance integer := distance(NEW.CONNECTIONID);
		passagierBonusmeilen integer := getPassagierBonusmeilen(NEW.KUNDENNUMMER);
		newBonusmeilen integer;
	begin
		if(distance <= passagierBonusmeilen) then
			NEW.Preis = 0;
			newBonusmeilen := passagierBonusmeilen - distance;
			update passagier set bonusmeilen = newBonusmeilen where passagier.KUNDENNUMMER = NEW.KUNDENNUMMER;
		end if;
		return new;
	end
	$payWithBonus$ language plpgsql;

	create trigger payWithBonusmiles before insert on buchung 
		for each row execute procedure payWithBonusmeilen();

    --3--
    create or replace function updateBonusmeilen() returns trigger as $update_bonusmile$
	declare
		newBonusmeilen integer;
	begin
		newBonusmeilen := getPassagierBonusmeilen(NEW.KUNDENNUMMER) + 0.1 * distance(NEW.CONNECTIONID);
		update passagier set bonusmeilen = newBonusmeilen where passagier.KUNDENNUMMER = NEW.KUNDENNUMMER;
	end
	$update_bonusmile$ language plpgsql;

	create trigger updatePassagierBonusmeilen after insert on buchung 
		for each row execute procedure updateBonusmeilen();

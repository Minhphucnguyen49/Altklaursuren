/***#1***/ 
   
    --1--
    CREATE OR REPLACE FUNCTION getFreeSeats(varchar, date) RETURNS INTEGER as $freeSeats$ 
		declare
			allSeats integer;
			bookedSeats integer;

		begin
			select fl.SITZPLATZ_ into allSeats 
            from abflug ab, flugzeug fl
				where ab.CONNECTIONID = $1 
                and ab.datum = $2 
                and ab.LUFTFAHRZEUGKENNZEICHEN = fl.LUFTFAHRZEUGKENNZEICHEN;

			select count (b.CONNECTIONID) into bookedSeats from buchung b, flugzeug fz, abflug ab
				where b.CONNECTIONID = ab.CONNECTIONID
					and ab.CONNECTIONID = $1
					and ab.LUFTFAHRZEUGKENNZEICHEN = fz.LUFTFAHRZEUGKENNZEICHEN
					and b.datum = ab.datum
					and ab.datum = $2;
					
			return allSeats - bookedSeats;
		end;
    $freeSeats$ LANGUAGE plpgsql;

    --2--
    create or replace function maintenance(VARCHAR(50)) returns void as $maintenance$
        declare
		flugKennzeichen varchar(10) := $1;
		heute date := current_date;
	begin
		if not exists (
			SELECT * 
			FROM wartung 
			WHERE wartung.LUFTFAHRZEUGKENNZEICHEN = flugKennzeichen
			AND wartung.datum = heute)
		then 
			INSERT INTO wartung VALUES(LUFTFAHRZEUGKENNZEICHEN, heute, false);
		else 
			UPDATE wartung 
			SET flugfreigabe = true 
			WHERE wartung.LUFTFAHRZEUGKENNZEICHEN = flugkennzeichen
			AND wartung.datum = heute;	
		end if;
	end
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
    CREATE OR REPLACE FUNCTION deg2rad(float) RETURNS FLOAT as $$
        DECLARE
            deg float := $1; 
            pi_value float := 3.14159265358979323846;
        BEGIN
            return deg * ( pi_value / 180.0);
        END
    $$ language plpgsql;

    CREATE OR REPLACE FUNCTION sqrt_for_get_distance(deltaLat float, deltaLon float, lat1 float, lat2 float) RETURNS FLOAT AS $$
        BEGIN 
    return asin
          (
           sqrt
           (
              (sin(deltaLat) * sin(deltaLat)) 
              + 
              cos(lat1) * cos(lat2) * (sin(deltaLon) * sin(deltaLon))
           )
          );
        END
    $$ language plpgsql;

    CREATE OR REPLACE FUNCTION getDistance( varchar, varchar) RETURNS float as $$
        DECLARE 
         deltaLat float default 0;
         deltaLon float default 0;
         res float default 0;
         lat1 float := (SELECT BREITENGRAD FROM FLUGHAFEN WHERE IATA_CODE = $1);
         lon1 float := (SELECT LANGENGRAD FROM FLUGHAFEN WHERE IATA_CODE = $1);
         lat2 float := (SELECT BREITENGRAD FROM FLUGHAFEN WHERE IATA_CODE = $2);
         lon2 float := (SELECT LANGENGRAD FROM FLUGHAFEN WHERE IATA_CODE = $2);

        BEGIN 
          lat1 := deg2rad(lat1);
          lon1 := deg2rad(lon1);
          lat2 := deg2rad(lat2);
          lon2 := deg2rad(lon2); 
          deltaLat = (lat2 - lat1) / 2.0;
          deltaLon = (lon2 - lon1) / 2.0;

           res := 2.0 * 6371.0 * sqrt_for_get_distance(deltaLat, deltaLon, lat1, lat2);

           RAISE NOTICE 'distance between (% - %) : % km',$1, $2, res;

           return res;

        END; 
    $$ language plpgsql;

/***#3***/

    --1--
    CREATE OR REPLACE FUNCTION enough_seats() RETURNS trigger as $$
        DECLARE
         seat_number integer default 0;
         BEGIN
          RAISE NOTICE 'ID: %   DATE: %',NEW.CONNECTIONID, NEW.Datum;
           seat_number := getFreeSeats(NEW.CONNECTIONID,NEW.Datum );
          IF (seat_number < 1) 
          THEN 
           NEW = OLD;
           RAISE NOTICE 'NO FLIGHT AVAILABLE! RETURNED VALUE IS 0. DATE and/or CONNECTION ID could be invalid';
          END IF;

          RAISE NOTICE 'SEATNUMBER: %', seat_number;

          return NEW;
        END;
    $$ LANGUAGE plpgsql;
    
    CREATE OR REPLACE TRIGGER enough_seats_trigger before insert on buchung 
    for each row execute procedure enough_seats();

    CREATE OR REPLACE FUNCTION update_seatnumber() RETURNS TRIGGER AS $$
    DECLARE 
        seat_number integer;
        registrationr varchar;

        BEGIN
          SELECT d.LUFTFAHRZEUGKENNZEICHEN INTO registrationr 
          FROM abflug d
          WHERE d.CONNECTIONID = NEW.CONNECTIONID 
          AND d.DATUM = NEW.DATUM; 

          seat_number := getFreeSeats(NEW.CONNECTIONID, NEW.DATUM) - 1;
           RAISE NOTICE 'NEUE SITZPLÄTZE %', seat_number;
          UPDATE flugzeug SET SITZPLATZ_ = seat_number 
          WHERE LUFTFAHRZEUGKENNZEICHEN = LUFTFAHRZEUGKENNZEICHEN;
          return NEW;
        END; 
    $$ LANGUAGE plpgsql;

    CREATE OR REPLACE TRIGGER decrement_seats_trigger after insert on BUCHUNG
        for each row execute procedure update_seatnumber();
    

    --2--
    CREATE OR REPLACE FUNCTION calculate_account_balance(connection_id varchar) RETURNS FLOAT as $$
        DECLARE 
         start_airport varchar;
         dest_airport varchar;
         bonus float;
        BEGIN

          SELECT c.START, c.ZIEL
          INTO start_airport, dest_airport 
          FROM FLUGVERBINDUNG c 
          WHERE c.CONNECTIONID = connection_id;

          bonus := getDistance(start_airport, dest_airport) / 10 ;

          RAISE NOTICE ' Bonus: %', bonus;
          return bonus;
        END;
    $$ LANGUAGE plpgsql;

    CREATE OR REPLACE FUNCTION trigger2_pay_with_Bonusmiles() RETURNS TRIGGER as $$
        DECLARE 
         account float default 0; 
         distance float default 0;  
        
        BEGIN    
         SELECT p.BONUSMEILEN into account 
         FROM PASSAGIER p 
         WHERE p.KUNDENNUMMER = NEW.KUNDENNUMMER;
         
         RAISE NOTICE 'account status old %', account;

         account := account - calculate_account_balance(NEW.CONNECTIONID);
         RAISE NOTICE 'account status new %', account;
        
        IF ( account >= 0 ) THEN
           RAISE NOTICE 'ist größer %', account;
           RAISE INFO 'Ihr Ticket ist kostenlos';
           NEW.preis = 0;

           UPDATE PASSAGIER SET BONUSMEILEN = account 
           WHERE KUNDENNUMMER = NEW.KUNDENNUMMER ;

        ELSE 
           RAISE INFO 'Ihre Ticket kostet: %', NEW.preis;

         END IF;
                 return NEW;
        END;
    $$ LANGUAGE plpgsql;

    CREATE OR REPLACE TRIGGER account_balance_for_flights_trigger before insert on Buchung 
        for each row execute procedure trigger2_pay_with_Bonusmiles();

    --3--
    create or replace function trigger3_updateBonusmiles() returns trigger as 
	$$
        DECLARE
          account float default 0; 
        BEGIN 
          SELECT BONUSMEILEN INTO account 
          FROM PASSAGIER p WHERE p.KUNDENNUMMER = NEW.KUNDENNUMMER; 

          RAISE NOTICE 'NEW CONNECTIONID: %', NEW.CONNECTIONID;
          RAISE NOTICE 'CURRENT ACCOUNT: %', account;
          account := calculate_account_balance(NEW.CONNECTIONID) + account;
          RAISE NOTICE 'Neuer WERT %', account;

          UPDATE PASSAGIER 
          SET BONUSMEILEN = account 
          WHERE KUNDENNUMMER = NEW.KUNDENNUMMER;

          return NEW; 
        END;
	$$ language plpgsql;

    drop trigger updatePassagierBonusmeilen on BUCHUNG;
	create trigger updatePassagierBonusmeilen after insert on buchung 
		for each row execute procedure trigger3_updateBonusmiles();

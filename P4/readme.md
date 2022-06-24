# Lösungsdokumentations-Template zu Praktikum 4

Diese readme.md dient als **Template** für Ihre Prozedur-/Funktions- und Trigger-Definitionen für Praktikum 4.

Nachdem Sie die Aufgabenbeschreibung zu Praktikum 4 (PDF-Dokument) abgearbeitet und Ihre Lösungen erfolgreich auf Ihrem Datenbankserver getestet haben, fügen Sie die Lösungen hier in die entsprechenden Felder unter [SQL-SELECT Statements](#sql-select-statements) ein. Diese Lösungen werden geprüft und Gegenstand des Praktikums sein.

# Zu beachtende Regeln!
Beachten Sie bei der Bearbeitung dieser Aufgabe folgendes:

### Regel Nr. 1
Formatieren Sie die Prozedur-/Funktions- und Trigger-Definitionen so, dass es einfach ist, diese zu lesen. Orientieren Sie sich hierbei (im Hinblick auf die Formatierung) an den folgenden Beispielen und achten Sie auch auf die Indents (Einrückungen):
```sql
create or replace function autosum() returns trigger as $autosum$
    declare
    	aktPreis integer;
    begin
    	select ProdPreis into aktPreis
    		from Produkt
    		where ProdNr = NEW.ProdNr;
    	update Rechnung
    		set GesPreis = GesPreis + aktPreis * NEW.anzahl
    		where RNR = NEW.RNR;
    	return NEW;
    end;
$autosum$ language plpgsql;
```  

```sql
drop trigger autosumtrigger on Position;
create trigger autosumtrigger after insert on Position
	for each row execute procedure autosum();
```

# 1 Stored Procedures
Implementieren Sie folgende Funktionen als Stored Procedures auf Ihrem Datenbankserver und testen Sie diese. Verwenden Sie, wenn nicht anders angegeben, die Sprache PL/pgSQL
1. Eine Funktion **getFreeSeats**, welche eine Flugnummer und ein Datum übergeben bekommt, und die freien Plätze auf diesem Flug berechnet und zurück gibt.
    ```sql
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

    ```
2. Eine Funktion **maintenance**, welche als Parameter ein Flugzeugkennzeichen entgegen nimmt, und für dieses Flugzeug einen Wartungsvorgang mit Flugfreigabe für den heutigen Tag erstellt. „Heute“ bedeutet das aktuelle Datum, mit dem die Funktion aufgerufen wurde. Beachten Sie hierbei, dass Ihre Funktion mit den folgenden beiden Fällen umgehen können muss:
    - Es gibt keinen Eintrag in der Wartungstabelle, daher muss ein neuer Eintrag erstellt werden
    - Es existiert bereits ein Eintrag, unter Umständen ohne Flugfreigabe
    ```sql
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
    ```
3. Eine Funktion (oder View), welche die gleiche Aufgabe erfüllt wie Aufgabe 1.12 aus dem letzten Praktikum (Ausgabe aller Passagiere inkl. aller Flugdaten). Sie dürfen hierfür auch eine Stored Procedure mit SQL schreiben.
    ```sql
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
    ```

# 2  Entfernungsberechnung für Bonusmeilen
Es soll ein Bonusmeilen System eingeführt werden, bei denen Passagiere bei Buchung 10% der zu erwartenden Reisedistanz auf ein Konto gut geschrieben bekommen. Diese Bonusmeilen können für Flüge verwendet werden.

Beispiel:
- Ein Passagier fliegt den Flug FRA nach LAX (Entfernung 9321km) und bekommt dafür 932 Bonusmeilen gutgeschrieben.
- Der gleiche Passagier (mit 932 Bonusmeilen) bucht erneut einen Flug, diesmal von Frankfurt nach Paris (Entfernung 449km). Die Bonusmeilen reichen also aus, um diesen Flug zu bezahlen. Dem Passagier werden demnach 449km von seinen 932 Bonusmeilen abgezogen, der Flug allerdings ist kostenlos.
- Ob Sie Bonusmeilen mit Nachkommastellen erfassen bzw. ob Sie für einen kostenlosen Flug erneut Bonusmeilen vergeben, bleibt Ihnen überlassen.

Um dies umzusetzen, implementieren Sie folgendes:
1. Eine Funktion **getDistance**, welche zwei IATA-Codes als Parameter erhält und die Entfernung zwischen diesen beiden Flughäfen berechnet.
    ```sql
    	
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
    ```
2.  Das „automatische“ Verarbeiten der Bonusmeilen wird in Aufgabe 3 als Trigger implementiert.

Für die Entfernungsberechnung auf einer Kugeloberfläche __muss__ die Haversine Formel verwendet werden. Das ist notwendig, da Sie nicht die "direkte" Route von Frankfurt nach Peking nehmen können, da diese zu nah am Erdkern verläuft.  
Diese Formel finden Sie in Moodle in der Datei `dist.c`, welche Sie als Inspiration für Ihren PL/pgSQL Code verwenden können.

# 3  Trigger
Sie haben bereits ein Attribut für Bonusmeilen in Passagier bzw. Kunde aus einem früheren Praktikum. Dies können und sollen Sie verwenden, um für jeden Kunden Bonusmeilen zu speichern.

Implementieren Sie die folgenden drei Triggerfunktionen und Trigger auf die Buchungstabelle. Verwenden Sie hierfür, wenn angebracht, die Stored Procedures aus Aufgabe 1 bzw. 2:
1. Einen *before insert* Trigger. Dieser soll überprüfen, ob auf dem gewünschten Flug überhaupt noch Platz ist, und gegebenenfalls den *insert* abweisen.
    ```sql
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
    ```
    ```sql
	create trigger checkFreeSeat before insert on BUCHUNG
	    for each row execute procedure freeSeat();
    ```
2. Einen *before insert* Trigger welcher überprüft, ob der Flug mit Bonusmeilen anstatt mit Geld bezahlt werden kann. Falls dies der Fall ist, werden dem Passagier die Bonusmeilen entsprechend abgezogen und der Preis der Buchung wird auf 0 € gesetzt.
    ```sql
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
    ```
    
    ```sql
	create trigger payWithBonusmiles before insert on buchung 
		for each row execute procedure payWithBonusmeilen();
    ```
3. Einen *after insert* Trigger, der die Bonusmeilen für den gerade gebuchten Flug berechnet und dem Passagier gut schreibt.
    ```sql
    create or replace function ...
    ```
    ```sql
    create trigger ...
    ```

**Hinweis:** Die Aufgabe verlangt, zwei Trigger als *before insert* auf die gleiche Tabelle zu legen. In diesem Fall werden die Trigger in alphabetischer Reihenfolge ausgeführt. Die Reihenfolge ist wichtig, da der Trigger aus 1 auf jeden Fall **vor** dem Trigger aus 2 ausgeführt werden soll.

Sie können allerdings auch Aufgabe 1 und 2 in einem einzigen Trigger realisieren, wenn Sie wollen. Nutzen Sie in diesem Fall die untenstehenden Platzhalter zur Dokumentation Ihrer Lösung.
```sql
create or replace function updateBonusmeilen() returns trigger as $update_bonusmile$
	declare
		newBonusmeilen integer;
	begin
		newBonusmeilen := getPassagierBonusmeilen(NEW.KUNDENNUMMER) + 0.1 * distance(NEW.CONNECTIONID);
		update passagier set bonusmeilen = newBonusmeilen where passagier.KUNDENNUMMER = NEW.KUNDENNUMMER;
	end
	$update_bonusmile$ language plpgsql;
```
```sql
	create trigger updatePassagierBonusmeilen after insert on buchung 
		for each row execute procedure updateBonusmeilen();
```

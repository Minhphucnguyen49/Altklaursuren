# Aufgabenbeschreibung zu den SQL-SELECTs

Diese readme.md dient als **Template** für Ihre SQL-SELECT Statements für Praktikum 3.
 
Nachdem Sie die zusätzlichen Daten (siehe Aufgabenbeschreibung Praktikum 3) in Ihre Datenbank geladen haben und Ihre SQL-SELECT Statements das erwartete Ergebnis (siehe bereitgestellte Lösungen in Moodle) liefern, fügen Sie diese SQL Statements hier in die entsprechenden Felder unter [SQL-SELECT Statements](#sql-select-statements) ein. Diese Statements werden geprüft und Gegenstand des Praktikums sein. 

Die Musterlösungen zu den einzelnen SQL-Statements werden Ihnen ausgehändigt, sodass Sie vor der Einreichung selbst kontrollieren können, ob Ihr Ergebnis korrekt ist. 

<br>

# Zu beachtende Regeln!
Beachten Sie bei der Bearbeitung dieser Aufgabe folgendes:

### Regel Nr. 1 
Formatieren sie die SQL-SELECT Statements so, dass es einfach ist diese zu lesen. Das bedeutet, schreiben Sie die SELECT-Statements **NICHT** in eine einzige Zeile, wie z.B.:    
```sql
SELECT  a.col1, b.col2, AVG(b.col3) AS avg, FROM table_a a, table_b b WHERE a.col1 = b.col2 GROUP BY a.col1, b.col2 ORDER BY avg HAVING (avg > (SELECT max(col1) FROM table_c)); 
```    
    
Schreiben Sie die Statements stattdessen mit den einzelnen SQL Key-Fragmenten (SELECT, FROM, WHERE, etc.) pro Zeile und mit den nötigen Indents (Einrückungen) auf, wie z.B. hier:
```sql
SELECT a.col1, b.col2, AVG(b.col3) AS avg
    FROM table_a a, table_b b
    WHERE a.col1 = b.col2
    GROUP BY a.col1, b.col2
    ORDER BY avg
    HAVING (avg < 
        (SELECT max(col1)
            FROM table_c));       
```  

<br>

### Regel Nr. 2 (WICHTIG!!!)
Machen Sie sich klar, dass Ihr SQL-Statement nicht dadurch automatisch korrekt ist, dass es die gleichen
Ausgaben liefert, wie sie in der Lösung stehen! Ihr Statement sollte die gestellte Frage beantworten, und nicht „rein zufällig“ die gleiche Ausgabe liefern.

Als Beispiel folgende **Aufgabe 0**:<br>
"Für welche Flugnummern haben Passagiere $200 für einen Platz bezahlt?"<br>
Das richtige Ergebnis ist die Projektion von Flugnummer mit dem einzigen Eintrag "**LH-200**". 

Ihre SQL-Abfrage darf **NICHT** folgendermaßen lauten:
```sql
SELECT flugnr
    FROM Buchung
    WHERE flugnr = "LH-200";
``` 
Das wäre eine vollkommen falsche Abfrage mit der zufällig gleichen Ausgabe. Durch solche SQL-Statements gefährden Sie die Erteilung eines Testats enorm! 

Korrekt wäre die Abfrage:
```sql
SELECT flugnr
    FROM Buchung
    WHERE Preis = "$200";
```

Zusätzlich können Sie auch gerne Erklärungen zu Ihren SQL-Select Statements schreiben, um zu erklären was da genau passiert, oder warum Sie sich für diese Query entschieden haben

<br>

Und nun viel Spaß bei der Generierung der SQL-Statements :-)

<br>

# SQL-SELECT Statements

1. Welche Flüge gehen am 01.10.2018? (geprüft)
    ```sql   
    SELECT abflug.connectionid, abflug.datum, abflug.luftfahrzeugkennzeichen
    FROM abflug
    WHERE datum='2018-01-10';
    ```
2. Geben Sie Name, Vorname und Flugnummer aller Passagiere aus, die überhaupt Flüge gebucht haben. (geprüft)
    ```sql
    SELECT passagier.nachname, passagier.vorname, buchung.connectionid
    FROM passagier
    INNER JOIN buchung ON passagier.kundennummer=buchung.kundennummer;
    ```
3. Wie 2, jedoch nur für Abﬂüge am 02.10.2018. (geprüft)
    ```sql
    SELECT passagier.nachname, passagier.vorname, buchung.connectionid
    FROM passagier
    INNER JOIN buchung ON passagier.kundennummer=buchung.kundennummer
    AND datum='2018-02-10';
    ```
4.  Geben Sie die Namen (und **nur** die Namen) der Flughäfen an, die von London Heathrow (LHR) aus angeﬂogen werden. 

-- fehlt nur noch Frankfurt Airport --

    ```sql
    SELECT flughafen.name
    FROM flughafen
    INNER JOIN flugverbindung ON flughafen.iata_code = flugverbindung.ziel
    AND flugverbindung.start = 'LHR';
    ```
5. Geben Sie die Gesamtsumme aus, die der Passagier „Michael Roth“ für Tickets ausgegeben hat.

(geprüft) (achte auf Klammer bei buchung.preis)

    ```sql
    SELECT SUM (buchung.preis)
    FROM buchung
    INNER JOIN passagier ON passagier.kundennummer=buchung.kundennummer
    WHERE passagier.nachname='Roth'
    AND passagier.vorname='Michael';
    ```
   
6. Geben Sie eine nach Anzahl der gebuchten Tickets sortierte Liste mit Namen und Vornamen der Passagiere sowie der Ticktanzahl aus.  

(geprüft) 

     ```sql
    SELECT p.nachname, p.vorname, COUNT(buchung.kundennummer) AS anzahl
        FROM passagier p
        JOIN buchung ON p.kundennummer = buchung.kundennummer
        GROUP BY p.nachname, p.vorname
        ORDER BY anzahl DESC;
    ```

7. Generieren Sie eine Liste, bei der alle Flüge mit der **Anzahl** der Abﬂüge ausgegeben werden. Sortieren Sie die Liste so, dass der Flug mit den meisten Abﬂügen ganz oben steht. 

(geprüft)

     ```sql
    SELECT a.connectionid AS flugnr, COUNT(a.connectionid) AS anzahl  
        FROM abflug a
        GROUP BY a.connectionid
        ORDER BY anzahl DESC;
    ```

8. Schreiben Sie eine Abfrage, welche Flughäfen anzeigt die **gar nicht** angeﬂogen werden. 

(geprüft, ausser WDH gibt es extra noch FRA, ich glaube aber meine Loesung richtig ist, weil als Ziel ist bei FRA nicht der Fall)

     ```sql
    SELECT fh.IATA_CODE AS iata
        FROM flughafen fh
        LEFT JOIN flugverbindung f ON f.ZIEL = fh.IATA_CODE
        WHERE f.ZIEL IS NULL;
    ```

9. Welche Flughäfen sind von Frankfurt aus nicht mit einem Direktﬂug, sondern lediglich **mit einem Umstieg** zu erreichen?

(braucht noch zu besprechen)

     ```sql
    SELECT fh.IATA_CODE AS iata, fh.NAME AS fhname , fh.LANGENGRAD AS lon, fh.BREITENGRAD AS lat
        FROM flughafen fh
        
        JOIN flugverbindung f ON f.ZIEL = fh.IATA_CODE
       /*WHERE f.START != 'FRA'*/

        JOIN flugverbindung f1 ON f1.
        WHERE 
        

    ```

10. Ist es möglich, am 03.10.2018 von Frankfurt (FRA) **über** London (LHR) nach Beijing (PEK) zu ﬂiegen? Geben Sie für jede mögliche Verbindung Startdatum, Startﬂughafen, Zwischenlandung, Zielﬂughafen **in jeweils einer Zeile** an. (Dabei wird davon ausgegangen, dass Folgeﬂüge am selben Tag noch erreicht werden können) 

(braucht noch zu besprechen)

    ```sql
    SELECT 
        a.datum AS Startdatum, 
        a.connectionid AS flugnr,
        f.START AS start, 
        f.ZIEL AS Zwischenlandung,
        f1.ZIEL AS Zielflughafen
        
        FROM abflug a  
        
        JOIN flugverbindung f ON f.connectionid = a.connectionid
        AND f.start = 'FRA' AND f.ziel = 'LHR'
        AND a.datum = '2018-03-10'

        JOIN flugverbindung f1 ON f1.START = 'LHR'
        AND f1.ZIEL = 'PEK';
        
    ```
/* JOIN abflug a1 ON a1.connectionid = f.connectionid
        AND f.ziel = 'LHR' 
        
        a1.datum AS zwischenstopp_start_datum
        a1.connectionid AS flugnr,*/
11. Wie viele Passagiere könnten theoretisch (bei voller Auslastung aller geplanten Abﬂüge) am 02.10.2018 von Frankfurt aus transportiert werden?

(geprüft)

    ```sql
    SELECT SUM(fg.SITZPLATZ_) AS max_sitzplatz
        FROM FLUGZEUG fg
        INNER JOIN abflug a ON fg.LUFTFAHRZEUGKENNZEICHEN = a.LUFTFAHRZEUGKENNZEICHEN
        AND a.datum = '2018-02-10'
    
        JOIN flugverbindung f ON f.connectionid = a.connectionid
        AND f.START = 'FRA';
    ```
    
12. Geben Sie eine Liste aller Passagiere inklusive aller Flugdaten aus:
    - Nachname
    - Vorname
    - Preis
    - Flugnummer
    - Flugdatum
    - IATA-Code des Startﬂughafens
    - Name des Startﬂughafens
    - IATA-Code des Zielﬂughafens
    - Name des Zielﬂughafens

(geprüft)

     ```sql
    SELECT 
    p.nachname, 
    p.vorname, 
    b.preis, 
    b.connectionid AS flugnr, 
    b.datum, 
    f.START AS start, 
    fh1.name AS start_name, 
    f.ZIEL AS ziel,
    fh2.name AS ziel_name
        
        FROM BUCHUNG b
        
        JOIN PASSAGIER p ON p.KUNDENNUMMER = b.KUNDENNUMMER 

        JOIN flugverbindung f ON f.connectionid = b.connectionid

        JOIN FLUGHAFEN fh1 ON fh1.IATA_CODE = f.START 
        JOIN FLUGHAFEN fh2 ON fh2.IATA_CODE = f.ZIEL; 
    ```

13. Generieren Sie eine absteigend sortierte Liste, die pro Flugzeugtyp angibt wie viele Passagiere in Summe bei voller Auslastung aller Abﬂüge befördert werden können.
(geprüft)

     ```sql
    SELECT fg.MODELTYP AS typ, SUM (fg.SITZPLATZ_) AS gesamt
        FROM flugzeug fg
        JOIN abflug a ON a.LUFTFAHRZEUGKENNZEICHEN = fg.LUFTFAHRZEUGKENNZEICHEN
        GROUP BY fg.MODELTYP
        ORDER BY gesamt DESC;
    ```

14. Welche Flughäfen sind am häuﬁgsten **Ziel** von Flugverbindungen?
(verzweifelt)

     ```sql
    SELECT f.ZIEL, COUNT( f.ZIEL ) AS anzahl
        FROM flugverbindung f
        GROUP BY f.ZIEL
        ORDER BY anzahl DESC;
    ```



































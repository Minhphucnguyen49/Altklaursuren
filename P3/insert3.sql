INSERT INTO FLUGHAFEN (IATA_CODE, NAME, BREITENGRAD, LANGENGRAD) VALUES 
('ATL', 'Hartsfield-Jackson International Airport Atlanta',  -84.4280556, 33.636667),
('PEK', 'Beijing Capital International Airport',             166.5975, 40.0725),
('DXB', 'Dubai INternational Airport',                       55.364444, 25.252778),
('ORD', 'Chicago O Hare International Airport',              -87.904722, 41.978611),
('HND', 'Tokyo International Airport',                       139.781111, 35.553333),
('LHR', 'Heathrow Airport',                                  -0.461389, 51.4775),
('LAX', 'Los Angeles International Airport',                 -118.408056, 33.9425),
('HKG', 'Hong Kong International Airport',                   113.914444, 22.308889),
('CDG', 'Paris Charles de Gaulle Airport',                   2.547778, 49.009722),
('DFW', 'Dallas International Airport',                      -97.038056, 32.896944),
('IST', 'Istanbul Atatürk Airport',                          28.814167, 40.976111),
('FRA', 'Frankfurt Airport',                                 8.570556, 50.033333),
('WDH', 'Hosea Kutako International Airport',                17.47095, -22.479894);


INSERT INTO FLUGZEUG(LUFTFAHRZEUGKENNZEICHEN, MODELTYP, SITZPLATZ_) VALUES
('D-ABBB', 'Airbus A330-300', 236),
('D-ABBC', 'Airbus A330-300', 240),
('D-ABBD', 'Airbus A330-300', 221),
('D-ABBE', 'Airbus A330-300', 231),
('D-ABBF', 'Airbus A340-300', 280),
('D-ABBG', 'Airbus A340-300', 271),
('D-ABBH', 'Airbus A340-300', 243),

('D-ABBI', 'Airbus A340-600', 266),
('D-ABBK', 'Airbus A340-600', 293),
('D-ABBL', 'Airbus A380-800', 509),

('D-ABBM', 'Airbus A350-900', 293),
('D-ABBO', 'Airbus A350-900', 297),
('D-ABBP', 'Airbus A350-900', 288),
('D-ABBQ', 'Airbus A350-900', 288),

('D-ABBR', 'Airbus A320-200', 168),
('D-ABBS', 'Airbus A320-200', 168),
('D-ABBT', 'Airbus A320-200', 170),
('D-ABBU', 'Airbus A320-200', 142),
('D-ABBW', 'Boeing B747-8', 364),
('D-ABBX', 'Boeing B747-8', 364),
('D-ABBY', 'Boeing B747-8', 364),
('D-ABBZ', 'Boeing B747-8', 364),
('D-ABCA', 'Boeing B737-700', 86),
('D-ABCC', 'Boeing B737-700', 88);

INSERT INTO FLUGVERBINDUNG(CONNECTIONID, START, ZIEL) VALUES
('LH-100', 'FRA', 'ATL'),
('LH-102', 'FRA', 'DXB'),
('LH-103', 'FRA', 'ORD'),
('LH-104', 'FRA', 'HND'),
('LH-105', 'FRA', 'LHR'),
('LH-106', 'FRA', 'LAX'),
('LH-107', 'FRA', 'HKG'),
('LH-108', 'FRA', 'CDG'),
('LH-109', 'FRA', 'DFW'),
('LH-110', 'FRA', 'IST'),
('LH-200', 'LHR', 'ATL'),
('LH-201', 'LHR', 'PEK'),
('LH-202', 'LHR', 'DXB'),
('LH-203', 'LHR', 'ORD'),
('LH-204', 'LHR', 'FRA');

INSERT INTO ABFLUG(LUFTFAHRZEUGKENNZEICHEN, ABFLUGID, CONNECTIONID, DATUM) VALUES
('D-ABBL', 1, 'LH-100', '2018-01-10'),
('D-ABBL', 2, 'LH-100', '2018-02-10'),
('D-ABBL', 3, 'LH-100', '2018-03-10'),
('D-ABBL', 4, 'LH-100', '2018-04-10'),
('D-ABBL', 5, 'LH-100', '2018-05-10'),
('D-ABBL', 6, 'LH-100', '2018-06-10'),
('D-ABBK', 7, 'LH-100', '2018-07-10'),
('D-ABBK', 8, 'LH-100', '2018-08-10'),

('D-ABBB', 9, 'LH-102', '2018-02-10'),
('D-ABBB', 10, 'LH-102', '2018-04-10'),
('D-ABBB', 11, 'LH-102', '2018-06-10'),

('D-ABBB', 12, 'LH-103', '2018-09-10'),

('D-ABBB', 13, 'LH-104', '2018-03-10'),
('D-ABBB', 14, 'LH-104', '2018-05-10'),
('D-ABBB', 15, 'LH-104', '2018-07-10'),
('D-ABBB', 16, 'LH-104', '2018-09-10'),

('D-ABBB', 17, 'LH-105', '2018-01-10'),
('D-ABBB', 18, 'LH-105', '2018-02-10'),
('D-ABBB', 19, 'LH-105', '2018-03-10'),

('D-ABCA', 20, 'LH-200', '2018-01-10'),
('D-ABCA', 21, 'LH-200', '2018-02-10'),
('D-ABCA', 22, 'LH-201', '2018-03-10'),

('D-ABBR', 23, 'LH-201', '2018-05-10'),

('D-ABCA', 24, 'LH-202', '2018-05-10'),
('D-ABCA', 25, 'LH-202', '2018-09-10'),
('D-ABCA', 26, 'LH-203', '2018-04-10'),
('D-ABCA', 27, 'LH-203', '2018-05-10'),

('D-ABCC', 28, 'LH-203', '2018-06-10'),

('D-ABBF', 29, 'LH-204', '2018-01-10'),  
('D-ABBI', 30, 'LH-204', '2018-03-10'),
('D-ABBM', 31, 'LH-204', '2018-08-10'); 

INSERT INTO PASSAGIER(KUNDENNUMMER, NACHNAME, VORNAME, BONUSMEILEN) VALUES
(1 , 'Roth'     , 'Michael'  ,           0),
(2 , 'Schestag' , 'Inge'     ,           0),
(3 , 'Störl'    , 'Uta'      ,           0),
(4 , 'Muth'     , 'Peter'    ,           0),
(5 , 'Peter'    , 'Thorsten' ,           0),
(6 , 'Ruehl'    , 'Stefan'   ,           0);

INSERT INTO BUCHUNG (KUNDENNUMMER, BUCHUNGID, CONNECTIONID, DATUM, PREIS) VALUES
(1, 11, 'LH-100', '2018-01-10', 100.00),
(5, 12, 'LH-102', '2018-04-10', 100.00),
(6, 13, 'LH-104', '2018-07-10', 100.00),
(1, 14, 'LH-100', '2018-02-10', 100.00),
(2 ,16, 'LH-100', '2018-01-10', 100.00),
(3 ,17, 'LH-100', '2018-01-10' ,100.00),
(1 ,18, 'LH-105', '2018-01-10' ,105.00),
(1 ,19, 'LH-200', '2018-01-10' ,200.00),
(2 ,20, 'LH-100', '2018-02-10' ,100.00),
(2 ,21, 'LH-100', '2018-03-10' ,100.00),
(2 ,22, 'LH-100', '2018-04-10' ,100.00),
(2 ,23, 'LH-100', '2018-05-10' ,100.00),
(2 ,24, 'LH-100', '2018-06-10' ,100.00),
(2 ,25, 'LH-100', '2018-07-10' ,100.00),
(2 ,26, 'LH-100', '2018-08-10' ,100.00);
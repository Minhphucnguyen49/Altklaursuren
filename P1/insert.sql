INSERT INTO FLUGHAFEN(IATA, NAME, LANGENGRAD, BREITENGRAD) VALUES 
('ATL', 'Hartsfield-Jackson International Airport Atlanta', -84.4280556, 33.636667),
('PEK', 'Beijing Capital International Airport', 166.5975, 40.0725),
('DXB', 'Dubai INternational Airport', 55.364444, 25.252778),
('ORD', 'Chicago O Hare International Airport', -87.904722, 41.978611),
('HND', 'Tokyo International Airport', 139.781111, 35.553333),
('LHR', 'Heathrow Airport', -0.461389, 51.4775),
('LAX', 'Los Angeles International Airport',-118.408056, 33.9425),
('HKG', 'Hong Kong International Airport', 113.914444, 22.308889),
('CDG', 'Paris Charles de Gaulle Airport', 2.547778, 49.009722),
('DFW', 'Dallas International Airport', -97.038056, 32.896944),
('IST', 'Istanbul Atatürk Airport', 28.814167, 40.976111),
('FRA', 'Frankfurt Airport', 8.570556, 50.033333);

INSERT INTO FLUGZEUG(KENNZEICHEN, TYP, SITZPLATZE) VALUES
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

INSERT INTO FLUG(FLUGNR, START, ZIEL) VALUES
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
('LH-203', 'LHR', 'ORD');

INSERT INTO ABFLUG(KENNZEICHEN, FLUGNR, DATUM) VALUES
('D-ABBL', 'LH-100', '2018-01-10'),
('D-ABBL', 'LH-100', '2018-02-10'),
('D-ABBL', 'LH-100', '2018-03-10'),
('D-ABBL', 'LH-100', '2018-04-10'),
('D-ABBL', 'LH-100', '2018-05-10'),
('D-ABBL', 'LH-100', '2018-06-10'),
('D-ABBK', 'LH-100', '2018-07-10'),
('D-ABBK', 'LH-100', '2018-08-10'),

('D-ABBB', 'LH-102', '2018-02-10'),
('D-ABBB', 'LH-102', '2018-04-10'),
('D-ABBB', 'LH-102', '2018-06-10'),

('D-ABBB', 'LH-103', '2018-09-10'),

('D-ABBB', 'LH-104', '2018-03-10'),
('D-ABBB', 'LH-104', '2018-05-10'),
('D-ABBB', 'LH-104', '2018-07-10'),
('D-ABBB', 'LH-104', '2018-09-10'),

('D-ABBB', 'LH-105', '2018-01-10'),
('D-ABBB', 'LH-105', '2018-02-10'),
('D-ABBB', 'LH-105', '2018-03-10'),

('D-ABCA', 'LH-200', '2018-01-10'),
('D-ABCA', 'LH-200', '2018-02-10'),
('D-ABCA', 'LH-201', '2018-03-10'),

('D-ABBR', 'LH-201', '2018-05-10'),

('D-ABCA', 'LH-202', '2018-05-10'),
('D-ABCA', 'LH-202', '2018-09-10'),
('D-ABCA', 'LH-203', '2018-04-10'),
('D-ABCA', 'LH-203', '2018-05-10'),

('D-ABCC', 'LH-203', '2018-06-10');


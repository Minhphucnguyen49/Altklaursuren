/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     09.05.2022 22:28:16                          */
/*==============================================================*/


drop index FLIEGT_FK;

drop index TERMINIERT_FK;

drop index ABFLUG_PK;

drop table ABFLUG cascade;

drop index BESTEHT_AUS_FK;

drop index BUCHT_FK;

drop index BUCHUNG_PK;

drop table BUCHUNG cascade;

drop index FLUGHAFEN_PK;

drop table FLUGHAFEN cascade;

drop index LANDED_FK;

drop index STARTED_FK;

drop index FLUGVERBINDUNG_PK;

drop table FLUGVERBINDUNG cascade;

drop index FLUGZEUG_PK;

drop table FLUGZEUG cascade;

drop index PASSAGIER_PK;

drop table PASSAGIER cascade;

drop index GEWARTET_FK;

drop index WARTUNG_PK;

drop table WARTUNG cascade;

/*==============================================================*/
/* Table: ABFLUG                                                */
/*==============================================================*/
create table ABFLUG (
   CONNECTIONID         VARCHAR(50)                 not null,
   LUFTFAHRZEUGKENNZEICHEN VARCHAR(50)          not null,
   ABFLUGID             INT4                 not null,
   DATUM                DATE                 not null,
   constraint PK_ABFLUG primary key (ABFLUGID)
);

/*==============================================================*/
/* Index: ABFLUG_PK                                             */
/*==============================================================*/
create unique index ABFLUG_PK on ABFLUG (
ABFLUGID
);

/*==============================================================*/
/* Index: TERMINIERT_FK                                         */
/*==============================================================*/
create  index TERMINIERT_FK on ABFLUG (
CONNECTIONID
);

/*==============================================================*/
/* Index: FLIEGT_FK                                             */
/*==============================================================*/
create  index FLIEGT_FK on ABFLUG (
LUFTFAHRZEUGKENNZEICHEN
);

/*==============================================================*/
/* Table: BUCHUNG                                               */
/*==============================================================*/
create table BUCHUNG (
   CONNECTIONID         VARCHAR(50)          not null,
   LUFTFAHRZEUGKENNZEICHEN VARCHAR(50)       null,
   ABFLUGID             INT4                 null,
   BUCHUNGID            INT4                 not null,
   KUNDENNUMMER         INT4                 not null,
   DATUM                DATE                 null,
   PREIS                DECIMAL                null,
   constraint PK_BUCHUNG primary key (BUCHUNGID)
);

/*==============================================================*/
/* Index: BUCHUNG_PK                                            */
/*==============================================================*/
create unique index BUCHUNG_PK on BUCHUNG (
BUCHUNGID
);

/*==============================================================*/
/* Index: BUCHT_FK                                              */
/*==============================================================*/
create  index BUCHT_FK on BUCHUNG (
KUNDENNUMMER
);

/*==============================================================*/
/* Index: BESTEHT_AUS_FK                                        */
/*==============================================================*/
create  index BESTEHT_AUS_FK on BUCHUNG (
ABFLUGID
);

/*==============================================================*/
/* Table: FLUGHAFEN                                             */
/*==============================================================*/
create table FLUGHAFEN (
   BREITENGRAD          FLOAT8               not null,
   LANGENGRAD           FLOAT8               not null,
   NAME                 VARCHAR(50)          not null,
   IATA_CODE            VARCHAR(50)          not null,
   constraint PK_FLUGHAFEN primary key (IATA_CODE)
);

/*==============================================================*/
/* Index: FLUGHAFEN_PK                                          */
/*==============================================================*/
create unique index FLUGHAFEN_PK on FLUGHAFEN (
IATA_CODE
);

/*==============================================================*/
/* Table: FLUGVERBINDUNG                                        */
/*==============================================================*/
create table FLUGVERBINDUNG (
   CONNECTIONID         VARCHAR(50)          not null,
   ZIEL                 VARCHAR(50)          not null,
   START                VARCHAR(50)          not null,
   constraint PK_FLUGVERBINDUNG primary key (CONNECTIONID)
);

/*==============================================================*/
/* Index: FLUGVERBINDUNG_PK                                     */
/*==============================================================*/
create unique index FLUGVERBINDUNG_PK on FLUGVERBINDUNG (
CONNECTIONID
);

/*==============================================================*/
/* Index: STARTED_FK                                            */
/*==============================================================*/
create  index STARTED_FK on FLUGVERBINDUNG (
START
);

/*==============================================================*/
/* Index: LANDED_FK                                             */
/*==============================================================*/
create  index LANDED_FK on FLUGVERBINDUNG (
ZIEL
);

/*==============================================================*/
/* Table: FLUGZEUG                                              */
/*==============================================================*/
create table FLUGZEUG (
   SITZPLATZ_           INT4                 not null,
   LUFTFAHRZEUGKENNZEICHEN VARCHAR(50)          not null,
   MODELTYP             VARCHAR(50)          not null,
   constraint PK_FLUGZEUG primary key (LUFTFAHRZEUGKENNZEICHEN)
);

/*==============================================================*/
/* Index: FLUGZEUG_PK                                           */
/*==============================================================*/
create unique index FLUGZEUG_PK on FLUGZEUG (
LUFTFAHRZEUGKENNZEICHEN
);

/*==============================================================*/
/* Table: PASSAGIER                                             */
/*==============================================================*/
create table PASSAGIER (
   VORNAME              VARCHAR(50)          not null,
   NACHNAME             VARCHAR(50)          not null,
   KUNDENNUMMER         INT4                 not null,
   BONUSMEILEN          INT4                 null,
   constraint PK_PASSAGIER primary key (KUNDENNUMMER)
);

/*==============================================================*/
/* Index: PASSAGIER_PK                                          */
/*==============================================================*/
create unique index PASSAGIER_PK on PASSAGIER (
KUNDENNUMMER
);

/*==============================================================*/
/* Table: WARTUNG                                               */
/*==============================================================*/
create table WARTUNG (
   LUFTFAHRZEUGKENNZEICHEN VARCHAR(50)          not null,
   WARTUNGID            INT4                 not null,
   DATUM                DATE                 not null,
   FLUGFREIGABE         BOOL                 not null,
   constraint PK_WARTUNG primary key (WARTUNGID)
);

/*==============================================================*/
/* Index: WARTUNG_PK                                            */
/*==============================================================*/
create unique index WARTUNG_PK on WARTUNG (
WARTUNGID
);

/*==============================================================*/
/* Index: GEWARTET_FK                                           */
/*==============================================================*/
create  index GEWARTET_FK on WARTUNG (
LUFTFAHRZEUGKENNZEICHEN
);

alter table ABFLUG
   add constraint FK_ABFLUG_FLIEGT_FLUGZEUG foreign key (LUFTFAHRZEUGKENNZEICHEN)
      references FLUGZEUG (LUFTFAHRZEUGKENNZEICHEN)
      on delete restrict on update restrict;

alter table ABFLUG
   add constraint FK_ABFLUG_TERMINIER_FLUGVERB foreign key (CONNECTIONID)
      references FLUGVERBINDUNG (CONNECTIONID)
      on delete restrict on update restrict;

alter table BUCHUNG
   add constraint FK_BUCHUNG_BESTEHT_A_ABFLUG foreign key (ABFLUGID)
      references ABFLUG (ABFLUGID)
      on delete restrict on update restrict;

alter table BUCHUNG
   add constraint FK_BUCHUNG_BUCHT_PASSAGIE foreign key (KUNDENNUMMER)
      references PASSAGIER (KUNDENNUMMER)
      on delete restrict on update restrict;

alter table FLUGVERBINDUNG
   add constraint FK_FLUGVERB_LANDED_FLUGHAFE foreign key (ZIEL)
      references FLUGHAFEN (IATA_CODE)
      on delete restrict on update restrict;

alter table FLUGVERBINDUNG
   add constraint FK_FLUGVERB_STARTED_FLUGHAFE foreign key (START)
      references FLUGHAFEN (IATA_CODE)
      on delete restrict on update restrict;

alter table WARTUNG
   add constraint FK_WARTUNG_GEWARTET_FLUGZEUG foreign key (LUFTFAHRZEUGKENNZEICHEN)
      references FLUGZEUG (LUFTFAHRZEUGKENNZEICHEN)
      on delete restrict on update restrict;


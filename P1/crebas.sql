/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     04.05.2022 11:48:06                          */
/*==============================================================*/


drop index FLIEGT_FK;

drop index TERMINIERT_FK;

drop index ABFLUG_PK;

drop table ABFLUG;

drop index FLUGHAFEN_PK;

drop table FLUGHAFEN;

drop index LANDED_FK;

drop index STARTED_FK;

drop index FLUGVERBINDUNG_PK;

drop table FLUGVERBINDUNG;

drop index FLUGZEUG_PK;

drop table FLUGZEUG;

/*==============================================================*/
/* Table: ABFLUG                                                */
/*==============================================================*/
create table ABFLUG (
   LUFTFAHRZEUGKENNZEICHEN VARCHAR(50)          not null,
   ABFLUGID             INT4                 not null,
   DATUM                DATE                 not null,
   CONNECTIONID         INT4                 not null,
   constraint PK_ABFLUG primary key (LUFTFAHRZEUGKENNZEICHEN, ABFLUGID)
);

/*==============================================================*/
/* Index: ABFLUG_PK                                             */
/*==============================================================*/
create unique index ABFLUG_PK on ABFLUG (
LUFTFAHRZEUGKENNZEICHEN,
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
   CONNECTIONID         INT4                 not null,
   IATA_CODE            VARCHAR(50)          not null,
   FLU_IATA_CODE        VARCHAR(50)          not null,
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
FLU_IATA_CODE
);

/*==============================================================*/
/* Index: LANDED_FK                                             */
/*==============================================================*/
create  index LANDED_FK on FLUGVERBINDUNG (
IATA_CODE
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

alter table ABFLUG
   add constraint FK_ABFLUG_FLIEGT_FLUGZEUG foreign key (LUFTFAHRZEUGKENNZEICHEN)
      references FLUGZEUG (LUFTFAHRZEUGKENNZEICHEN)
      on delete restrict on update restrict;

alter table ABFLUG
   add constraint FK_ABFLUG_TERMINIER_FLUGVERB foreign key (CONNECTIONID)
      references FLUGVERBINDUNG (CONNECTIONID)
      on delete restrict on update restrict;

alter table FLUGVERBINDUNG
   add constraint FK_FLUGVERB_LANDED_FLUGHAFE foreign key (IATA_CODE)
      references FLUGHAFEN (IATA_CODE)
      on delete restrict on update restrict;

alter table FLUGVERBINDUNG
   add constraint FK_FLUGVERB_STARTED_FLUGHAFE foreign key (FLU_IATA_CODE)
      references FLUGHAFEN (IATA_CODE)
      on delete restrict on update restrict;


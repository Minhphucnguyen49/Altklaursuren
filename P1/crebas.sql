/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     27/04/2022 18:47:05                          */
/*==============================================================*/


drop index R2_FK;

drop index R1_FK;

drop index ABFLUG_PK;

drop table ABFLUG;

drop index R4_FK;

drop index FLUG_PK;

drop table FLUG;

drop index FLUGHAFEN_PK;

drop table FLUGHAFEN;

drop index R3_FK2;

drop index R3_FK;

drop index FLUGZEUG_PK;

drop table FLUGZEUG;

/*==============================================================*/
/* Table: ABFLUG                                                */
/*==============================================================*/
create table ABFLUG (
   FLUGNR               TEXT                 not null,
   FLU_FLUGNR           TEXT                 null,
   DATUM                TEXT                 null,
   KENNZEICHEN          TEXT                 null,
   constraint PK_ABFLUG primary key (FLUGNR)
);

/*==============================================================*/
/* Index: ABFLUG_PK                                             */
/*==============================================================*/
create unique index ABFLUG_PK on ABFLUG (
FLUGNR
);

/*==============================================================*/
/* Index: R1_FK                                                 */
/*==============================================================*/
create  index R1_FK on ABFLUG (
FLU_FLUGNR
);

/*==============================================================*/
/* Index: R2_FK                                                 */
/*==============================================================*/
create  index R2_FK on ABFLUG (
KENNZEICHEN
);

/*==============================================================*/
/* Table: FLUG                                                  */
/*==============================================================*/
create table FLUG (
   FLUGNR               TEXT                 not null,
   IATA                 TEXT                 null,
   ZIEL                 TEXT                 null,
   START                TEXT                 null,
   constraint PK_FLUG primary key (FLUGNR)
);

/*==============================================================*/
/* Index: FLUG_PK                                               */
/*==============================================================*/
create unique index FLUG_PK on FLUG (
FLUGNR
);

/*==============================================================*/
/* Index: R4_FK                                                 */
/*==============================================================*/
create  index R4_FK on FLUG (
IATA
);

/*==============================================================*/
/* Table: FLUGHAFEN                                             */
/*==============================================================*/
create table FLUGHAFEN (
   IATA                 TEXT                 not null,
   NAME                 TEXT                 null,
   LANGENGRAD           DECIMAL              null,
   BREITENGRAD          DECIMAL              null,
   constraint PK_FLUGHAFEN primary key (IATA)
);

/*==============================================================*/
/* Index: FLUGHAFEN_PK                                          */
/*==============================================================*/
create unique index FLUGHAFEN_PK on FLUGHAFEN (
IATA
);

/*==============================================================*/
/* Table: FLUGZEUG                                              */
/*==============================================================*/
create table FLUGZEUG (
   KENNZEICHEN          TEXT                 not null,
   FLUGNR               TEXT                 null,
   IATA                 TEXT                 null,
   TYP                  TEXT                 null,
   SITZPLATZE           INT4                 null,
   constraint PK_FLUGZEUG primary key (KENNZEICHEN)
);

/*==============================================================*/
/* Index: FLUGZEUG_PK                                           */
/*==============================================================*/
create unique index FLUGZEUG_PK on FLUGZEUG (
KENNZEICHEN
);

/*==============================================================*/
/* Index: R3_FK                                                 */
/*==============================================================*/
create  index R3_FK on FLUGZEUG (
FLUGNR
);

/*==============================================================*/
/* Index: R3_FK2                                                */
/*==============================================================*/
create  index R3_FK2 on FLUGZEUG (
IATA
);

alter table ABFLUG
   add constraint FK_ABFLUG_R1_FLUG foreign key (FLU_FLUGNR)
      references FLUG (FLUGNR)
      on delete restrict on update restrict;

alter table ABFLUG
   add constraint FK_ABFLUG_R2_FLUGZEUG foreign key (KENNZEICHEN)
      references FLUGZEUG (KENNZEICHEN)
      on delete restrict on update restrict;

alter table FLUG
   add constraint FK_FLUG_R4_FLUGHAFE foreign key (IATA)
      references FLUGHAFEN (IATA)
      on delete restrict on update restrict;

alter table FLUGZEUG
   add constraint FK_FLUGZEUG_R3_ABFLUG foreign key (FLUGNR)
      references ABFLUG (FLUGNR)
      on delete restrict on update restrict;

alter table FLUGZEUG
   add constraint FK_FLUGZEUG_R3_FLUGHAFE foreign key (IATA)
      references FLUGHAFEN (IATA)
      on delete restrict on update restrict;


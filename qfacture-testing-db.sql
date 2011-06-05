-- MySQL dump 10.11
--
-- Host: localhost    Database: qfacture-testing
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny5

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `article`
--

DROP TABLE IF EXISTS `article`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `article` (
  `aID` smallint(5) unsigned NOT NULL auto_increment COMMENT 'ID de l''article',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce produit',
  `name` varchar(255) NOT NULL COMMENT 'Désignation de l''article',
  `price` decimal(10,2) NOT NULL COMMENT 'Prix unitaire',
  `comment` text NOT NULL COMMENT 'Brève description',
  PRIMARY KEY  (`aID`),
  KEY `a_owner` (`u_ID`),
  CONSTRAINT `article_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COMMENT='Table des articles';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `article`
--

LOCK TABLES `article` WRITE;
/*!40000 ALTER TABLE `article` DISABLE KEYS */;
INSERT INTO `article` VALUES (1,1,'Truc cher !','2005.07','Juste pour tester'),(2,1,'Prod de test','50.00','toto'),(3,1,'Trucdfgdfsg','5.00','bla bla');
/*!40000 ALTER TABLE `article` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `client`
--

DROP TABLE IF EXISTS `client`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `client` (
  `cID` smallint(5) unsigned NOT NULL auto_increment COMMENT 'ID du client',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil auquel est rattaché ce client',
  `name` varchar(255) NOT NULL COMMENT 'Nom du client',
  `address` varchar(255) default NULL COMMENT 'Adresse',
  `complement` varchar(255) default NULL COMMENT 'Complément d''adresse',
  `zip` varchar(5) default NULL COMMENT 'Code postal',
  `city` varchar(255) NOT NULL COMMENT 'Ville',
  `phone` varchar(14) default NULL COMMENT 'Téléphone',
  `mail` varchar(255) default NULL COMMENT 'Adresse mail',
  PRIMARY KEY  (`cID`),
  KEY `c_owner` (`u_ID`),
  CONSTRAINT `client_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COMMENT='Table des clients';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `client`
--

LOCK TABLES `client` WRITE;
/*!40000 ALTER TABLE `client` DISABLE KEYS */;
INSERT INTO `client` VALUES (2,1,'Kévin Gomez','35 rue de vichy','','63360','Gerzat','0698568827','contact@kevingomez.fr');
/*!40000 ALTER TABLE `client` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `facture`
--

DROP TABLE IF EXISTS `facture`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `facture` (
  `fID` mediumint(8) unsigned NOT NULL auto_increment COMMENT 'ID de la facture',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil ayant créé cette facture',
  `c_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du client',
  `tr_ID` tinyint(3) unsigned NOT NULL COMMENT 'Mode de règlement',
  `td_ID` tinyint(3) unsigned NOT NULL COMMENT 'Type de document',
  `amount` decimal(10,2) default NULL COMMENT 'Montant total de la facture',
  `comment` text COMMENT 'Commentaire',
  `Date` char(10) default NULL COMMENT 'Date de la facture',
  PRIMARY KEY  (`fID`),
  KEY `idClient` (`c_ID`),
  KEY `f_owner` (`u_ID`),
  KEY `td_ID` (`td_ID`),
  KEY `tr_ID` (`tr_ID`),
  CONSTRAINT `facture_ibfk_4` FOREIGN KEY (`tr_ID`) REFERENCES `types_reglements` (`trID`),
  CONSTRAINT `facture_ibfk_1` FOREIGN KEY (`c_ID`) REFERENCES `client` (`cID`) ON DELETE CASCADE,
  CONSTRAINT `facture_ibfk_2` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE,
  CONSTRAINT `facture_ibfk_3` FOREIGN KEY (`td_ID`) REFERENCES `types_documents` (`tdID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COMMENT='Table des factures';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `facture`
--

LOCK TABLES `facture` WRITE;
/*!40000 ALTER TABLE `facture` DISABLE KEYS */;
INSERT INTO `facture` VALUES (5,1,2,3,1,'2055.07','sqsdqfsdq','2011-05-30');
/*!40000 ALTER TABLE `facture` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `factures_lignes`
--

DROP TABLE IF EXISTS `factures_lignes`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `factures_lignes` (
  `lID` mediumint(8) unsigned NOT NULL auto_increment COMMENT 'ID lien',
  `f_ID` mediumint(8) unsigned NOT NULL COMMENT 'ID facture',
  `name` varchar(255) NOT NULL COMMENT 'Désignation de l''article',
  `quantity` smallint(5) unsigned default NULL COMMENT 'Quantité',
  `price` decimal(10,2) default NULL COMMENT 'Prix unitaire',
  `off` decimal(5,2) unsigned default NULL COMMENT 'Remise (%)',
  `designation` text,
  `base_article` mediumint(8) unsigned default NULL,
  PRIMARY KEY  (`lID`),
  KEY `idFacture` (`f_ID`),
  CONSTRAINT `factures_lignes_ibfk_1` FOREIGN KEY (`f_ID`) REFERENCES `facture` (`fID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COMMENT='Lignes des factures';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `factures_lignes`
--

LOCK TABLES `factures_lignes` WRITE;
/*!40000 ALTER TABLE `factures_lignes` DISABLE KEYS */;
INSERT INTO `factures_lignes` VALUES (4,5,'Prod de test',1,'50.00','0.00','toto',2),(5,5,'Truc cher !',1,'2005.07','0.00','Juste pour tester',1);
/*!40000 ALTER TABLE `factures_lignes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `template`
--

DROP TABLE IF EXISTS `template`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `template` (
  `teID` smallint(5) unsigned NOT NULL auto_increment COMMENT 'ID du template',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce template',
  `type` varchar(10) NOT NULL COMMENT 'Type de template',
  `name` varchar(255) NOT NULL COMMENT 'Nom du template',
  `content` text NOT NULL COMMENT 'Contenu du template',
  PRIMARY KEY  (`teID`),
  KEY `te_owner` (`u_ID`),
  CONSTRAINT `template_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Templates de facture';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `template`
--

LOCK TABLES `template` WRITE;
/*!40000 ALTER TABLE `template` DISABLE KEYS */;
INSERT INTO `template` VALUES (1,1,'html','Thème par défaut','<html>\r\n<head>\r\n	<style type=\"text/css\">\r\n	/* GENERAL --------------------------------------------------------*/\r\n\r\n	* {\r\n		margin: 0;\r\n		padding: 0;\r\n	}\r\n\r\n	body {\r\n		background: #fff;\r\n		color: #393939;\r\n		font-family: Arial;\r\n	}\r\n\r\n	img {\r\n		border: 0;\r\n	}\r\n\r\n	p {\r\n		margin: 0px;\r\n		padding: 0px;\r\n	}\r\n\r\n	/** logo **/\r\n\r\n	#page-top-outer {\r\n		background: url(images/top_bg.jpg) top center repeat-x;\r\n		border-bottom: 1px solid #7e7e7e;\r\n		height: 92px;\r\n	}\r\n\r\n	#logo {\r\n		float: left;\r\n		margin: 45px 0 0 45px;\r\n	}\r\n\r\n	#logo h1 {\r\n		color: white;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 30px;\r\n	}\r\n\r\n	/** Contenu **/\r\n\r\n	#content h1 {\r\n		margin-bottom: 10px;\r\n	}\r\n\r\n	#content {\r\n		color: #333;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 12px;\r\n		line-height: 18px;\r\n		padding-top: 2em;\r\n		padding-left: 4em;\r\n		padding-right: 4em;\r\n	}\r\n\r\n	/** Tableaux **/\r\n\r\n	table {\r\n		border-collapse: collapse;\r\n		margin: 10px 0;\r\n	}\r\n\r\n	th {\r\n		height: 50px;\r\n		padding-left: 10px;\r\n		padding-right: 45px;\r\n	}\r\n\r\n	td {\r\n		border: 1px solid #D2D2D2;\r\n		padding: 10px;\r\n	}\r\n\r\n	/* Détails d\'une facture */\r\n\r\n	.align_left {\r\n		text-align: left;\r\n	}\r\n\r\n	#invoice_mentions {\r\n		margin-top: 20px;\r\n	}\r\n\r\n	#invoice_right_part {\r\n		text-align: left;\r\n		float: right;\r\n		margin-top: -120px;\r\n	}\r\n\r\n	#invoice_customer_name  {\r\n		font-weight: bold;\r\n	}\r\n\r\n	#invoice_products {\r\n		text-align: right;\r\n		width: 100%;\r\n		margin-top: 30px;\r\n	}\r\n\r\n	#invoice_products tfoot td {\r\n		border: none;\r\n	}\r\n	\r\n	#invoice_compagny_infos {\r\n		text-align: center;\r\n	}\r\n	</style>\r\n</head>\r\n<body>\r\n<div id=\"content\">\r\n	<div id=\"invoice_compagny_logo\"><img src=\"{% logo_url %}\" alt=\"\" /></div>\r\n\r\n	<p id=\"invoice_compagny_adress\">\r\n		{% ae_name %}<br />\r\n		{% ae_address %}<br />\r\n		{% ae_zip %} {% ae_city %}\r\n	</p>\r\n	\r\n\r\n	<p id=\"invoice_mentions\">\r\n		N° SIREN : {% siren %}<br />\r\n		Dispensé d’immatriculation au registre<br />\r\n		du commerce et des sociétés (RCS) et<br />\r\n		au répertoire des métiers (RM)\r\n	</p>\r\n	\r\n	<div id=\"invoice_right_part\">\r\n		<p id=\"invoice_customer\">\r\n			<span id=\"invoice_customer_name\">{% customer_name %}</span><br />\r\n			{% customer_address %} {% customer_address2 %}<br />\r\n			{% customer_zip %} {% customer_city %}\r\n		</p>\r\n\r\n		<p id=\"invoice_date\">\r\n			{% invoice_date %}\r\n		</p>\r\n	</div>\r\n\r\n	<span id=\"invoice_number\">Facture n°{% ref %}</span>\r\n	\r\n	<p id=\"invoice_desc\">\r\n		{% invoice_comment %}\r\n	</p>\r\n	\r\n	<table id=\"invoice_products\">\r\n		<thead>\r\n			<tr>\r\n				<th class=\"align_left\">Désignation</th>\r\n				<th>Prix unitaire</th>\r\n				<th>Quantité</th>\r\n				<th>Montant (EUR)</th>\r\n			</tr>\r\n		</thead>\r\n\r\n		<tbody>\r\n			{% product_line %}\r\n			<tr>\r\n				<td class=\"align_left\">{% designation %}</td>\r\n				<td>{% prix_unitaire %}</td>\r\n				<td>{% quantite %}</td>\r\n				<td>{% montant %}</td>\r\n			</tr>\r\n			{% product_line %}\r\n		</tbody>\r\n\r\n		<tfoot>\r\n			<tr>\r\n				<td class=\"align_left\" colspan=\"2\">Total HT</td>\r\n				<td colspan=\"2\">{% invoice_amount %}</td>\r\n			</tr>\r\n			<tr>\r\n				<td class=\"align_left\" colspan=\"3\">TVA non applicable, art. 293 B du CGI</td>\r\n			</tr>\r\n		</tfoot>\r\n	</table>\r\n\r\n	<p>\r\n		À régler par chèque ou par virement bancaire :\r\n	</p>\r\n\r\n	<table>\r\n		<tbody>\r\n			<tr>\r\n				<td>Code banque</td>\r\n				<td>Code guichet</td>\r\n				<td>N° de compte</td>\r\n				<td>Clé RIB</td>\r\n			</tr>\r\n			<tr>\r\n				<td>12222</td>\r\n				<td>22222</td>\r\n				<td>22222222222</td>\r\n				<td>22</td>\r\n			</tr>\r\n			<tr>\r\n				<td>IBAN N°</td>\r\n				<td colspan=\"3\">FR22 2222 2222 2222 2222 2222 222</td>\r\n			</tr>\r\n			<tr>\r\n				<td>Code BIC</td>\r\n				<td colspan=\"3\">Code bic</td>\r\n			</tr>\r\n		</tbody>\r\n	</table>\r\n\r\n	<p id=\"invoice_compagny_infos\">\r\n		{% ae_name %} – {% ae_address %} – {% ae_zip %} {% ae_city %}<br />\r\n		Telephone : {% ae_tel %} – Site Internet : {% ae_web %} – E-mail : {% ae_mail %}<br />\r\n		N° SIREN : {% siren %} – Code APE 6201Z\r\n	</p>\r\n</div>\r\n</body>\r\n</html>');
/*!40000 ALTER TABLE `template` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `types_documents`
--

DROP TABLE IF EXISTS `types_documents`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `types_documents` (
  `tdID` tinyint(3) unsigned NOT NULL auto_increment COMMENT 'ID du type de règlement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de règlement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de règlement',
  PRIMARY KEY  (`tdID`),
  KEY `td_owner` (`u_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `types_documents`
--

LOCK TABLES `types_documents` WRITE;
/*!40000 ALTER TABLE `types_documents` DISABLE KEYS */;
INSERT INTO `types_documents` VALUES (1,1,'Facture'),(2,1,'Devis');
/*!40000 ALTER TABLE `types_documents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `types_reglements`
--

DROP TABLE IF EXISTS `types_reglements`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `types_reglements` (
  `trID` tinyint(3) unsigned NOT NULL auto_increment COMMENT 'ID du type de règlement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de règlement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de règlement',
  PRIMARY KEY  (`trID`),
  KEY `tr_owner` (`u_ID`),
  CONSTRAINT `types_reglements_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `types_reglements`
--

LOCK TABLES `types_reglements` WRITE;
/*!40000 ALTER TABLE `types_reglements` DISABLE KEYS */;
INSERT INTO `types_reglements` VALUES (1,1,'Espèces'),(2,1,'Chèque'),(3,1,'Virement');
/*!40000 ALTER TABLE `types_reglements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user` (
  `uID` tinyint(3) unsigned NOT NULL auto_increment COMMENT 'ID de l''utilisateur',
  `te_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du template utilisé',
  `name` varchar(255) default NULL COMMENT 'Nom de l''utilisateur',
  `address` varchar(255) default NULL COMMENT 'Adresse ligne 1',
  `complement` varchar(255) default NULL COMMENT 'Complément d''adresse',
  `zip` varchar(5) default NULL COMMENT 'Code postal',
  `city` varchar(255) default NULL COMMENT 'Ville',
  `mail` varchar(255) default NULL COMMENT 'Adresse mail',
  `phone` varchar(14) default NULL COMMENT 'Téléphone',
  `siret` varchar(17) default NULL,
  `website` varchar(255) default NULL COMMENT 'Site web',
  `logo` blob COMMENT 'logo',
  `fac_reference_format` varchar(255) default NULL COMMENT 'Format des références des factures',
  PRIMARY KEY  (`uID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Utilisateurs de Qfacture';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,1,'Julien PECQUEUR','30 rue Charles Labbé','APPT 10','80000','AMIENS','jpec@julienpecqueur.com','0649869072','527 958 821 00011','http://www.julienpecqueur.com','�PNG\r\n\Z\n\0\0\0\rIHDR\0\0,\0\0\0�\0\0\0d[��\0\0\0sRGB\0���\0\0\0bKGD\0�\0�\0�����\0\0\0	pHYs\0\0\0\0\0��\0\0\0tIME�\n;7��\0\0\0iTXtComment\0\0\0\0\0Created with GIMPd.e\0\0 \0IDATx��y��wY&������=���NU%�$�\"			�P�1Pe\n�6ܾ݊(q�mAׂQh���}A{ݥ\\��}mm�vd�f��L��Ré:���7������bd��e}���s�x�{��>��}^�#r1M��	r�&\0\0�\0�N~Hn��a�Н��g؟]�����s_ϭ�q�����^���\0�K�_���?\0�/�~o��b,�b=�=�\0j��H�k�k\0���N�	��ho��g��4h�>�ޜ����g�;]��=U��z��*����F�����R�.\0�V�/\r��\'�j��Z\0�b-\0�Rs\0u�N��\0Ղ�J�\Z0�����*P��H���g��.w����ؖ�|	��	d�{�)\0��\rxk��X��hl���?\0���Z�`}���:�J���P�j���	�-h����AN��c�נB�\\	B�%(W�Iz��Y��t�uL�2l\\E�	��lx��=8w�U�Nn�`�s|˥`�3�p-���\r��,Fux��+;����\0�A5;���3P&��J���Եܖ��N���]�3��!X��d��A)�L�f&d�n��nz{�����\rB�`3���j�!�x�	�v[\0+ǈy\r>����x�ܙ�e\\�Z�`}��5k��\04Ϧ��P+灲�(��J(�A�B�\Z*8)�����kJ��\'�}�;n߰l��u��#V��\n=�c�.�3X{KԀѰ�1;ƨ�N�N:�x�߹���9��^޷:v�&zĚ��!��(�-p�A�׈C^\Z#�Ėu��E�e�\0��Z\0ַ&P���5��u���Z�\0�3��([B���P���q�.��v���ک���ǣ�1��Gs�4a\r@��\"2�&�\"��0M\0��\0�G��E&��jEG�Fߪ#��~i�R��s��o���s��q��XB1x��!��k�\nq������!b��3��!��s-�k����\rV׬�F���·�\ZA�)@�T���PYe2(v��Bu,tf��Uݽ���;W��\'�.^��Ja���!\0�\01A�!@##�	V]��hBG@S��E4��C�A�	���ܺo��������l�\'�|���a�\"Y� 65b�A��D��:b���k���MVo��~u�\\P�\nZ[�\Z�:C�a*ϡ�����=��zE#��:w��𪍭�;wJu�@\0�HA)�4A+B	�J��`��@���a��#�@��#�\nb\"�8\"#ƨ�\\��!��:�k`?�{9���=o�Skν�G�|� �\"8��B]#�%�h���Z��UD\0X���Z\0�7�8��9V�����7mu�t��͠�Cwsha�L��7>�}�{7�95�O+?:�PJ�V0J�\ZBn�\"8&EP�@ ��Gǩ��#W@��g��`fp��s�1Fpd(fXD�#4#�	���\\ݵ�o������zh�|���F��� nX�=B[*��#��!N��M��o{Z��\0���7\'�g�Н9h�B�=4\'�����w��lc}���#����eYk4�VPZ���c<<��	�Z��Ĳ�39�7�1+f��^�#b�R,���� ���6�#�&@��:2�ُ\\t��_����n	6�F;\\T#�O�ē�M�����m-����`ղ�:�5�@�z�C#�^.`\n�պ.Nܱy���ᵓI�!�QA)c�\"c4\"iDE��PJ�k	F+L\"!3®\"H��\"hJ�5{��\n8U	�j\"#������#b���S��1�0Å�q���eu#���|D1t�_]*>p΁�__x��_��y9l���<�f�������뽳���kX_?�ڻur\r*k�;=(�Aw�`��L^#��A��1\\;z��k�w��J�<(M�XiD����6\nF˱��Ť�iB$Ѭ8	�\"�GP�Q�j�c�o��A	��2PJƈ!F��Ç ��#bЊ!�#�\0����]\'S�����G]��O�9��)#j\\� \r?���1Ġ�m�]G�s|�*��h-��>��k��OV��\njhxh����0���v�B���8����;/�_k�Z��P�Ff4�р�(2�n�`���\nD\n]��V	h5\0�����`	�0dGP8]F�AUd*��3-�!�%ǘF�#\Z� C�+��bDO1�<8D��U���������>�Qq�&�u��&5�Y�G��;\'k��uē��Xߢ�|�+\07ͼU��a	Z��Y�&@C��`�.��yyj���[�=wkؼ�AC�F�\"3�d\Z�\nX)�\0�H�+�L���08�	��1ɮ_��i�%-�#\0�f���egD`0X2E@r�)�p�@!�R5 �8Fh(@kTA�_.&�{�c;��>t�%�u����о�v\"jh4����ځ8��q��Ssm�I/�b-�CfWs`Պ��!t�@�e�az�O�]�|�\n:G���+�?:|�N�U�V�4��F�T�\\��FTr(-����v�:H%Reǯ\n��IDOJ��Xˁm��1�(������t�,Y����z��>�ĺ\"\nD�4�t�T�Gp�]œ�0�`����o�8�l�Q�1|�!	�_yq��k��Xބ����u(�Aw3aT��	�R;�(V�[��ǟq߉�K��xuM�@�r�Aǀ�Fn5����Hih��2\nF2�����6��c4pQ�R�	�JJC�ܶYD��ج���V�<�44�2��3�v�Jv#3E��T@CbR�\nІPyF���6����Y�ލsn��}�.���t6�\ZUSBe�1���m�\nH�����\\��� �+1-@k��Y��f����^���@S�����2dP�*н��������g}���\r.s�hc\r��+]�h�� +G�ˑ�En�Rh,e\n�&��\n��\"�^����H�\0��y`�gVsB����i�%E`�����_!1�����Z)(�P*X��s)� 0;��j@(���7WO�՗�$�x7���q�z\0`r`�p�Hz���&޼8;kX_�Z�q��!�5e<���Q��Jd���Ş�}�:��n9zÑ������������6�2e-�ܠ�\r��Ba9��D�V1z�Q�gW#�%F��oդ�P�h�0@�c�0$����L��)21LbU1�(�b�Y�R˾42M�J�*7�,�P��QU��hT_q�ͥ݅=���;�8T\0;���\r0���ܹ\r�@+=��kX�X��z��u	�vA��`�Y/CF����X�W�}�s�~����u\r���z���,`�X�Yd�0�Na��5����Yi��������4�)��r�G�\n�2�h04�,\\�Z�;0i�:\0c2ac�J��Uj�A~ƾ��]Ŗn�,M\0�Wh�F�`u�2��1\"�Ml�˖e���Ƿwu5ݷwi�hpm�79�m�r�m��-���\0�`Z��\0��Vo��P�A���%��\Z���6\"��<��d���C����?z�V���t�-T&�JY�\"��{zl,la��k`�F�\n�@p���HD(��D+�g������0�m�Y΄���nD<o��u�QhB�\0C��4/\r�_k^�:C9��,N�[-�a�?\n�\"����Z�]�V�\Z�����gJ׵?4�)�V����]�q\r�+e\0��T�r7x�=�y��Gz�Z�`����𦔁���a99d��G��o���C��~�����sXi��\rL.��ͥ�3���,V�ݎEa5&^X���#U_=�\Zi7PR\\�3\Z����7��a#�+��9-Yi�9Y\n[+�0���˾!dJ��\n��[��f�-f��\n\r��hd\n�|D�	���������:���%�/i���`�S��������q�^�����`���	�5���`,`X��Ͳ���E��|*hk*�0�%���Y�k:�2�;M}��~��n�T߫��2��� \Z�Yhk�3�,3�ձX�jTP��Z�.Ĳ���@A��TaV��\r��v�ЫB�cT>��\'ciƢ�*�D�L�c����B�\020!D�\n>&�@,�@������8]Fd\n��S�GN\n��`���a���&n瀝��?�>}�}����v`��\r8t�Q	�.X��5`\r��u\0�N�3�����b=B֬<l��·b��a�K04BF\nY�#�@g9C���O}��NlN���M���7l-Ln��Yn�+,��-��A\"���+�IJ>E\0=��i��1	�Y��C�b���\Z v�1T�5}+�f��tv�*\0�}*0C)�T1����\Zi�V��5��N*��&�&�cD�ڮ�ߵ��La��|�z�BD�\"bd��������I~���۵ɪ�!6\r��n�؀�%����\'�(\r�\rX|�ؒ�\0�v��e(`���6ϐ��m����X��[����勬U}e\rjm�;yn���{���1�U9&���?�1s���הAʲ�+5_&��Z�i��>X~�g>#��^*�zF�o�����\"�����M��:��bL-aXT^�ў%4�1q�A�з��JB\0�B�J�7��+e�(��Jɧe�k����ܣ/�}{�ʻ�8q\0j\0p��j�Z�2\'��B�Z�G.`1��3�j��lzP�Xd�G���u�r��O����L�O[6bS�\n�<���zݎ�#@A�hI6���g߶������JE���U���ixj_ <�-A+aGM0��3%@�]3\"f��B\"�ժ�j/���@����Q�JA�xƨ��X)ˆ1l\"�zV���D\"�V����Q@$���h\'�� �ey���{J(\"�ap��f�%�\0G\r���$�O��Z�o�R߰R0CC��tw\0�6�y^htv[,MN�.>vr���|��\Zl\rlnD`�,z����VB�H\Z��P<�t4�l�$ԥR.K�Q�s-�X���ju`�t-�b	�bt��3T�����R��ʼ�s.w���q������T�a5���C�U2B�~[�\0�K��m��3vu4r#Y^[\r��B77�D(���5\n�*�~���X����w�_�(��Y���ab�Q����%�5k ��5�3-N��z\0֜��\nСU��\n����a*�r�,x�V�X�OMyΗn_���W9e((�^n`2ѫ]���Y�4��RJ�F�SK��Ph}Wz�Ͳ�WkҮL�k)�����H�U�3w	xV�n5�������3�BMo��,im1�����	\Z���B�8�V�cwW@$�\r���F�\0P)�S��%����uzc�Q�=��S��U�=�!��Z��P����n�h-�#�a���5�ɱ��m]\ra\r`��]e���=wo=c<i��&�5�B�*���V��_us�匐kq��Ĕt*�Ħ@�	�f���t-V2#���ܶ+\'���u	�����T_Z�	]CS�K�<��?б�1��q�����ĶR�K�(�$ڕ\"hM��G,g��|��ң����Bn����* a��\0��U�V��������g��by@�B#�\n60L���`uA_1�HLk���[���>_��A�_��n�N��!S��f(\n�޾+���W�s�΋F{+�ɤ��}����{������[B�\n#%^�Z2bE����K�\'H��%���$\"�!�r^�r\'��\0����4����\0\"�gZ@���<j��(�$z�A�[\"�ձ�\Z�g�<��N\Z1�r��*a�R���� S(�\0��EX��ԁ�UT> �\"��.��-����n/�����/o��5#���c���u�W����Ů�b=V*?�i��[0�\0�l���%�ޒ\n{6և׌�p�\"e\r��\"���==�,�1�:���]\0kpn!,��@H�VH�R�H�_k�\\-�����X�g�\\l�9���-��+�+t���L\Z	���X�˶�kw��\"�ͪ0�i�e�㴄T�t���\\�x|P���B��� ����T+°�[�@�1q�����s��ؚ����n^H�b��t	F����u�Ǭ\'ۛ��b}c���8�������hY�E�.tC�F4��Y�b鞻N?����IV���e��rG#jO\n�(�4��\ṛtr/%�����M�$��,h��fF饅��8�pPc�[�}L@a�] T^��ʧ���Ɋ�	��,�-.L�+����`g��6c1�k,)˹B��Ԯ�]E��h,\Z��aݵQcw�`O���va�X�Ra0�8���LEۓ\'��黿��g>nc���B�.��r��\"����eu�k���JB�c/h�Q�������\r�]�U�\\Ơ��b���}�l<�T�/I�M�JϢ[4�`�#��u��\'VI#2h�ɞ�#O�������\"�I�\"��ݵ�^V���0s�kE�Zz��r��F���5P� �������BawGa%W��p��W��Ȓ0�åҲ��%�4����~���N��*@�1���Q��(��Gt�Bn��E�.`�cTh|w�5w.�l�|p`�&��@�X0w�c^x��Z����mX���a�}>Ծ4�[�f\n�f�D�,e��}����=]~�N4���A��`�a���$��-�l���B�K�0�`w&ǲ��b]�<�	�m��<������&�t�Dq��(/)�:�dT�-��vu�0�LIf����ZG���VJ�B2-ֈ�s\ZpA����PLA�����e�PbY1rk�\rn\r�L�F80*��A@���{��!\\�cTq�|��86��0,9��a�\r,�zֿ�a�cn%��J�E�cq�u|��I�*ڳ����1[7Ȳ��ȗ5z���[[�˨�2���\r������RG����).}\nHHe�&I�))�a�$ˆ�7�}�	=͘@B���9ng\n�U9����⽊S��P���)3��K������S��w��Q ��C!2�m��E��rҲsiƮ]��vX�\'\rc%��ԑOc�<C��&�\r���!��-�Ȁ&8��������v���.�?����:F́�����jΏ�1�:c�&�K�3p����b}U���f��5k �\r�\r������Y�A��1���𱣉;T��6�-�����j,u\r�Bö~�T2�TvE�4�8�G ������:�\'%NqaY1B�ȓ�!�¨Gp�rG�Sz`��J\0+L͢\"R)r&8/�yd�rs㿘P���Ef:�M��L��i�aJqpY�V�\0���ҌA�V`aZ[%c�p^_��G#Ā���8bk��Q8w�������aJװw��4��u��*T�#�n�&�ww������ܺд�4����oR�vu͵PG?�e�|�%j-@�.t1��<�\\![��rr����J��h����9�����2�����$�8#����\r0P<৥!��Q���mU\Z.1�F1��#�#�c��������4E��Sy�&��(}��B1��e��R�U���@P��	{B����c�W�4��	`f�*`5W�(�`k��;�]����q�������Bc�. r@Ոƕ�;�h��|��w�Ԡ�i6w��\'¤R��l�N������~�艈5D����\0�9��J_����_���w|�������ly�9��s⿟�;f�Q�s���d�����W�U�h�0X)2�d�s�@\Z�4F�H�BL:x&AXTk�$�j#d@b&{ƉZ��\Z�7l$����@F��9�9D/��!Ĕ\"\Z%�80�k{�����vB�;M��*|��Y\r��c�Sv(\"6@#�M��Ĥe5��J�K;.��.e0Fca��\Z�D9�a�P��������1�\"�;����O:���	ǡ����t�3��>��d�����\r��^؊c�D`����`5�s�g]�<w��\0XLw�}�R��#�W3x�bp�i���O\Z�wd��8r{�m�)S�L�`ݹ�V���g1��d��֩�$JqD�t,̩Pg��6p���I�����@C�]j�F3b��a(������h\Z\'3]��)�s*�M�\'�\nI�hjQX~62c�|��S��V�ϙ�[F�C�\r�/�8�/�=��(M�f\0\0 \0IDAT�I\0�`Y36\',��0��P��&40!\"��I��Q�a�=�Չ�����������5���Y���͍&n�rjg�7�F@9�(4��,�X����>T�;�Q�i=���O~Ҟs�=���	�Ye�t��]�/\"�}g��]`���o��[%�q�@k�:V!�)�$&�r2B^\'J��t�V��K83Ʀr�\nªbjT\Z/e\\b\0���P7����G];/�b��w*]D��t-��yE��\"�i�.�l�a;>l����6��a�1��La�<FޣjX&C3P�\n�	h��j��(%z�*��Ҁ���$m��eF�\"F�]C�!�1����f1��Q��S���.|9���vw��j��p�㕯|���`=2���,ʟu�t�,�q��\0ֱ�o�K]��������9j\\@`��M��5|�\r�\"�h�8�Cب5kJ��@�Py6����F�6l�H��R�y�Ӯ\0di�3/ ��G`�`\0{X8��A�4h�MӠi\Z����o&�CD�r,�.-k�\r+�뙒]ʺ��[J�|�;)Tl��亷\Z0�����ac�v�&�#PՄ��\nSF)%+��	y`��i� p�vMX�\Z�3i`\\@U1\nM������S��l��[�t���u�r�a&�&NFλ�G�\n��,�xX��#�]� � դ����eax(����o��ov?u�_~��C?���s�(��̌H�H\"\r	��c��[@e���2�o��`A�f��	�X�뀀V���6�9G�9�n\0%̊��� �\Z��BS���U5AU�h�\ZM� ��/	�kB�L6�!@�Naֲ��Bk\n�]�nzmRV��d�bǨ�vB4�MD�#&�(S�*?�\n%mtk�d\n\\�0f�����	��4�g�I _֌�������>�fgk�I�I�q����ѕ��G01����둢]�9�:�J��X5W���ǉs�\r�\0��~�����w��]��q͵��K.Q���M��$,�4@+T�\0Ҙ8��2��Ja����[(tT\n,����w�D#�{��d�B�.�!�fR�^�s��p���{hW�*\'��h&��!����A<z�2�z�~Ĵϭx��\\��a����?z��_���o���7��\0��u�:���\'��z�����sw:��w�@��Ç�U�e���\r�\Z���QFB�\nFk*|���*\0\Z[A�SXd��:bi�\r�g����,!�&��NǻN�ռ��d\r08��Cp�K�j����h�r����=7<�q8�oqۖǩ2J\ny>�,Ҫ#���paV��.��=p\Z��#�t��g�S�^���0+�U��)��I*jMj�f���_n[�G�du�$��	6i��)X��J�!�������FЎ&TpV�e\nN+xK�5!���Ԃe=W�m[\0Wx���o_��׽��o�\0�000�+��P�O�kkΕ�Z�x�6fy4\Z��xt����.�d�fEkTQK���w�qlQ9`�!4���ƠЈZ�\Z��1��>e�|U )��:3��mב!���0�5E���\Z�.1\Z�01���Ӟ�x��i��x|i+�2Ȕ(�Ĥ\Z���%R���)�Y��W?T1�ǃf)m0`j�s��l6�Tz6A���=V$�1�AӁ��\\hI0\r�Z{��R��R�>Yd���X��˝SJ�\0�	Q%p\"�jAQ�����T+\r�4�?QJu������w�w�������=����}��m�Uv�Ȋ6�;��#G��h�`r8��b�&A�R\Z[cc�U�?\"�g��\\˟�~*���⊁��m�3&\'�E��ڴ˭~�QJ��ab�T(\'cT�!����㺫�ǧOyl��8��k��S/��:l\"P�$�(�l�\\Kp_�l:2-.��r#~�������z�C�	�����0I^<H��k\n#Y��¨�ô�[�ѳ���C$`T��r\0&0tT�P�Ra3c*.�8�P�X�����<��O}�G?��GX��I�a&���>}�\0k��l\0�ђ�-���B�כ���q=2��2vA��I� \"0%��\"�,#��:5�:��\\%��`yֆc�=z3��!�|�G9�b\0W�M&h�	���]u>>s:L�1�yj6��u���i^�t�P�����j��6�Rr�r.;u�:\n���RN)�x������@Rf֩/0Dy��%�Z��i�t��E����4�\\�M�lt̽����Qo��%\0��#t$��h��#����X��iA��o��V>�Ⱦ�f���}��A�@*B\\t���{�!l���c4P\0�1�X���.yk⹵&��(9��2`�U�ĨB�-X��Ҵ�P��:�2�\n�`�2�\0��7�u��ㆧ]�;v�`5D�d�����A-}/��m�U�ځ&^F�K�;a��p��༁ƹ}��=��<��!Z�fF>��(�PB��X�n��$5hW�Qyqշ����ja�\"|�M�	��m}M�0f��Y�3n�D�K\ZO-��j���X_����w��g`_�a}}K�#���52�E?\Z]��:`�E8RL�Z#3���wۤAb��ʔ�2J��Ĩ�<�:��(�_�+yU\" �`�0�0���������.�9=����܏H�X4M-�ߺ�3�1Z�i>����EH\Zh?S�UȱR(t��P.2�����v�n�CD�Cǘ4Һ3v��Z��4������3~����R�x�GƤv�8c@���J���k��S��X�5[�6�<��o�_`������N�݇.�l��+����M@5�����?��>��\"�����Dpϖ���O�\\:��Y+��;�	� ��W�K��\"4{Dxw\r��� �Faw4��iVS����x�K��:�lH�\'�IM\'�(M�GFf�Knz?5���oFD��a&���/�޻I	�<G[�S�m�:��iB^ծ�0�Ja�R\n��$�gT���iZ������\'̕�󀅯��E�a��b���?�����4�o�%\'�:)t�����|�wQ�DF�N8�f�II�\0[���4�-�%aʿj���y���`�#<�w�t��<?�PN���y�����}ZpK��\'َ�o��h���j�4i�񩔜�E��-3J�åD���@D��0(�$^�1Q>�\0ˤLx1���j_\0�!BG���A�lg���}�������;]���U�\'`)8a~�E����yԿ�:�K�kO��P�B!��5q���w`2)�-� �wC��OR�jM�y�;N\0��gó\\fJ�U�����`��E4QzUl��Јs3Z\"H��u��Y,��-Iq_)O#@z G\rc��8]F�ONM\"vRYWaS���\00�)�<�3�pdٝDbP�����LM��;��S��JJS℩�P\0�mrRY8/������p�d9c�c�bV�k�.�;]|�5�/x��y����3�H�A�Q�c��N?v�v\r��dP��AҰBқ���-�OI��x`O��3Il�ә:Ne#+��z���0�;�2�!�0�hB�U�\\��>ΕL$e�kG8�+����e03����{x��gn�=<�Y�;�Rina��Ǩ\\iҹ�[�u[+�Mӥ��[ڵ�Q���w���ZA�L�\\#��#3�4����DpJR�Jj|��l\0�~�-�j�g������Z�bb��Pa�t�,�ꥥ�����O?�y����_���_YY�s�[r�\0�	��&;��ɰ8L��K?}u�߻~�Bw�2*4Q�(��dg��n��(F2Z!*+���\"����פ5f�1��F����{��r�\n8C��)yt����9f��	!N�V�Q�F�5�D鹁V���?��r3ʱ����g�?�%<�U�o�\ni��V�YE�O\"���a���g�21��T�B�Ù���R��-�d}pi�P��i�2����s���2����1��X��e�9ѝyJ2�������o��!B0<�я~�]���o��w��/�\r���[���_~����C�ЮŹ�-��YZՃM����W��K�s��~���Q2�f�\0�!B����lom�[ip2Z�h�V�(:	4�UC,��Z�h��m����4�0�Zav�O��\'��e1�iU��Ѧ;��~�N!%�\"�nϼ�e���?��>��?�9�jYV;\"l�\"�4�9Ĺ�:�f��*�(�̉t�i]�/��;�>B�Z��J��������\\	�!��[�=u�L��V|�!��KKK�W�W?�~}�u�}�)Oy�V��^xa��׾��/|��s�=~���믿��N�:e����Rg��_X=l\Zֿ{�K���^X��k*�+\0Ȍ�dgǎ�!\"ٍR\0�l;F�9	������V(g�<r�դ�:�I�_ou����)u�	�\\����=�K ٖ=F͢���n��ɲ��F��zs�n�,fo�Ӛn$�L�:SV?�ډA�v�F%��z���a�`p�Lc� C��&��t%F��V�Bk�{QS �r�Ө�aeY6�T���%_���|�+?\n\0�N���ַ����y�-��T����Y3s���wvv֎;ry���!�[G�f��)����(���Q\r���D%�ҨC�0��f��7���aޢ��&��<r�����xn�0$ cF�D���(����}rJ��q�J&�\Z����ڴ��&B��7�\0m��v��ex��΀k~�P�V�o�Hblڒ�(Bar����Gp��>A>X��\n,@�fl̮cV��K�F���go��<�O�|��&�������gc�b��CݙY0�O�.z=�K���@͞Ѱ�{��}V�sH�s��\\��\n�Y�H���� �\n�.q����8A���4M�h\"a�s��*��MV+&O�V���Iê���N�\'A�*�d���4LU��\0�@A�]ڍ�s,n��n\0x��OEp���P$�9�,���S�	�7W,C�4bH�����\\�d0?�{��$���«����Iׂ��S�K#����;����_\\|�Sf����o|�yPZCi��F��Ï���%W=?���e��?���@�����\\��u��S��LJ��;?��{՝��~�C�ե��/,�UA�������\'~⮇�_��_>���5&�R����?���_9x�`y������-oy˓?���_����d�u��`���:<p�������p�7�y���9R�����w|�c{��S�v�������W^y��o��u�]w�AO8c~Q)�R�~F�}�{�G~�G�\0k�/(����{o���w�n�����s��(�7��R*23B:ƨ����^x�7��~�_|��YK>`M&��o�l����Ovv������߆����{/����5?UW�\rU�<�q�2�=��-���7�\ní\r��8Mj�gXIKӿ�ێ��W`��;��	C�8Z��V8Y�R�a?弟}h�-��ӳ�lN�9�m<�bm����c>���-Ui�����h�	�����+�ߍ��~�����ݍ��7P����W�;\\��N�?�՝x�/��x�j<�w>����܊K��ԙ�ϳ��_����G��nԓ��O~���M��3x��OAf��7G��������kތ�}�(����x��݊^�K \"�>z״c����ף������N���o��r����������/|���ί���o��w<\\`\0���g���_|��,~����jo�+_�g�|3�t�}���U�z՟�c�}����x�s�󜟸뮻��t�M���;����|��o|�������ꯞ������=�~7�|��/��5��������}���?��/���|��_��[n��������^��gWU�������{�sY]������O�q���\0;v�mox��{]��\r7���y�|�����_����c?�cQ�u�4M�����#o��?���<\Z���_��}�����o`1󮪪~�5�:��S��Wh�/ R��RVkE�� i����ўąU|�����M�Y@���-��j*�D6�0\'E����T�WG`�Jfu����_h��L�4O��@\'<��<��x�K���g��^����k���=a���>�{�]^MZ�@�-�8�=�\0<��S�\0������dz�+��}XZ]���1W�:���_0��qO��[ۋ�UӒp�QWM��v�����`	�y�+p����~�o�/\n��������y�����v�5���MK¤׭,�������q\0x��~�3����?�~���$��~�g����7�p����UW]5}��w^�����﮽��O����\'�����?��������>�O���ɟ����ϯ.���ɫ_��;���/����tcc�?�����:��׼�����#��o��mo���W_��g<c��~��>���|�?�w�y�����i�y�s����p�����^�s���Yߞ={ܛ���/��Ç���{��<���_��=����뗾��_ZYY��^{�ƛ����`fzӛ��Cy��\0kgg���	�f�ڌ�6P)A�P�[�4�D�: `�)�������<�\"�L&����\Z�1�9)��r�TR��	\Zs�%Ѯ��ΡN�+i�ѐ�h͗U����ʘw=gOg\0�	�S{\0ۢ���9a�S�D�?&\0���J�fd,}j����Ƀ?��޲���\\�LS���9�G�Qt�IS_��U7n6�I��_��}�O1�\r�;���֩ӗ@��F\0�����E�|�/]�F��/���\00�Ƈ�<���a�7~�\0����/����W{���������<����;���]��^\0x��^���{�6&�����бc�����:u���O��c������? ?�q���}���D?����_��˿������_r}�w}�:\0lnn��~���o��y\Z�(��<I0�ҟ���6/��-�\"��!v�6�Hħ76��*���fD*�y\0pn��ML�J�T�Y _�<Z�G[�A�\rj���0I\0�)��P���i)/�|�n�V�ny>�/�is��g��R:�( �<.`���U觀�B�V���i:C�\n->��U�e\n�ttډ�Q|WS@\n1\rumu{>3�\"y�x�U^x�c�_�BM�?{o&�U]���ދȵ��w�\"��uKHBhɶ\0������1�f4����c@���ǘO���Fcv$@BB,R��Ջ��ڷ�\"�-w�x/2���������/�ʪʌ���w��s�=�N4�I\0���4��������_�ώ���)v����+��u�l6�7�8x�e�mߺu�z_���]��O~���s��/���W����߿��o=��lVJ�R��K/}�H�{�߸��K/�n��;������zϺu���mo{�Hϻ袋��;�;���ĳ�N�Z�Z��T*폺�����X����RȢth��p=�Y� _�Z\r��b(���\"��&C*fY�N�+�1��\"`uɛ�ٮ�*}[Kn���<�H��e���8����}�#` ���\"��:9��C��Hk)X-���B�a�H����Ȳ�1�K����nvv���!�K\r��1j��b�P��P�<�뾠���H�4�g���@�j�H``tm��`h�QW�(��7�����3���Ux��.�(ױ=U������goڴ������K^�����p�9�s��Ï\\}��7<���u�]=��ӑ��:묅��<��\Z\0�WJ��Y�Vm�*�\r7�pb��<ڹ_������?�я���F>�k=���{�@�PH�>�����gOv�ϔ�Ϙ��$K�e]�RWm��7?��u����X��Ls�f�\06:�l����o֖���(+`����.��u���V��z�\'�)���`�׫��菀��	�1�?�d}~�\\��!�i)p�g\n�!�W7@,�p�R��m9�kTwZ���v�\'>�Jٴ�P���vJI�H�9X 3�a�/��f��ګ�v��*���c�\0�hK�$��}�V�T������?�_�����?�������?��~����_?������׿~�g���X�Q���e�]v���{����߿\0Ƕo߾U\0�iӦ�G{�3�����O~򓁣��������X\0��K��H��T.��7UEj�	��<C��m��oF�¾jAH \0\0 \0IDAT�3F��H�aR�f<=3ìbf�LN��H��ۧ�o@b�xcm�o���s���#����*\0�˞䛦[XȀ��GU!\r,ƀV�Y�1�$t���Y�����EX���w\r����w��2�R(��ˇ|��#->Lk�a��F���w�r�s�l<�O\n8�pֵ_�1V��\r��}������������]8�_���K_s饝};::z�5%IR2�ǵɒ$)�Ȭ�h�=묳����B�x��#\0(���ɾ֧��\0�gϞ�g?�����������o����������p�\r[n��Vw�=�������h֭֙���9��ޥ~O��A�$�hnn\Z�z�Ė�\n8[�1E^�i��^<�x������O�	~�]<R\n2�V�5%`]�GXE�i�6�l)�OK\"LY&>�8ϣ,�L5��Q�Dx|(`,O��W���\'�M�\0����j�&A�	D=-����{sn*�������/���>�ŷv�w�u%�΂�h�������\n�,��_~}���������{Q�J~���w�Yf~w�������_�1��d�[�n2\0��\"����B���h�ݻwo�]޾}nI����,��\n*T��\'�Z��s^|���m����x׻��򹹹ޙ��rvO{��կ~e�c!����Vّ�a�\rc``����Q��Ÿ �R$#E�=��J\0�iJ�Xóss� d3�lQ�ł)e?^=c�b�\nP-�J-��j2�O�iO]!����:�U�����=�|��r�5���{�\\�c^B���jcxΪ��a�?Gca�����U�Cex5\\��$�M9����eGzx^T���$%N>�8��@��0A\'hK\0)	H�e-樼�o���/|�3�޻g�k�U|�_���V���|�}�\'r��ߝp�	�w��u��������F�����s�ڵӳ���ccc��|}�w��(�=���^X###�\\555U:B�Y��[�֞�k}��y��W_y�	\'�>�����}�y_��.�Z�/}�KO��}�\'���f�[k���bt`��h�Fw�u���O��6q� �������ng���;\r��h�N����k��k,4�:���ࠍk`�8�����U0w��gc���񲆃-�`�o��s��AԵ�.j��Z0����U�vU��Em��$�⥞�˴\r�-�p;��g\0\0�#Ꮇ���������^��J�\0�K�rm#Z�\Z�?��`)�u�\n������(Q\ncl��_�����\0kRRL��ܽf��ſ���~�H�W����Nں����G�O��t�5׌�?��+~�qj�Q�Wuң�C��g=�Y�m}�2���^�1<gGoo�4k˖-`ǎ��ܛn�itpppv����\'�Z��sJ)ݩ��Z�Ї>��?��?�&\0|��8����O�p���N��@���s����	c��:�VK$IK��;)�\\הW���h4��Z^� (3���� k˒��=�]��� _5큧���Z�G~��&��:�P\r����?@k^ө���[����:�2��?�]\'�����\r՝�G�ݜQ����ڭ���@B��o\\�Lg��\'\'�	��ۧp�~k	ظ�&�%$9/Mo��\'�6�@�나ŌL�%hfCE�	d���[o�_��w!�w)evHR߀�#)E��7to��70^��W��K�V\0[�D�#\Zc����V�e�����?���W��t�׼�5��G?���	|>��lݶm���k�ۿ��\rOgYV��?��#�&\'\'�|�+���=�i��/�����x�ۻ1_����ϼ��~�T�֧�GZ�_~�=�W��HӴ�G�G�<�������}�d�GAs����Jޒ�:CN)�b��\Z�&��If�)1�fQ!�� �m1;g��ia�D���v�=n���RyCꀙk{�}�����\\*�0�llcM`_O����R5�Gs�뼞\\�oᲂ#�b�x5ṟ2���Z�����ř	|��v��\'H�ML�݉y�[p�{����C��\0�kG�Ӝ��P;\rn��ï_��_�q����(9m�/�c\'5��+���,�]��r�OP���@�\r�q>����M[�A�f�f��k��=�}�+<??���?����3���o^�~��)������<3�������w�uW�c%���w<#���o^߽������_~��6nܸ��>����o}�\'IR:��3���.�v������F_���V���/|�?���_u�U_�+`�jվ�}��zE�����y����9��/xi��*]z�_��7��1]t������o����g���/|�k����믿~��/|�����\'>񉛞���d�9??�.��m])�	y���?��|Ma���/�ʟ��n���WG���/���s����P���+T*T*e��%��%�J%�E�_�[�?$$�[efa6#$������q�ͼg��f|z>�z����h�wt}c۶�ͺu�G�SM\'�В�b��TD��F1�V��;{��ƲwL�L|����`��l*�\0��HEhTm�6`s��Na~j�~�%��>�4�t�쿼�1o�6�;��Ă1>���<�����E)��q\0_bƃ?��y���g�$0��8������/D�h���g\r�Y���7�߯�����;.\\���G���0:���jl9�����ܣ��7��|�[��G��N=�����lt�����}�/��]�X�)�H��r���_�����bm�糟��\'_��F�H+��˘��]f&k���?��{׻�uϣ�(�;���ի^������\ry�7����>wǎ[z��\r\r\r�]p��|�#��p*�o~󛣯}�k_>555|��\'?x�9�<t�I\'���g?[u�u�m����y�[�������w=�5}�<�C���=��\"���љ��>{�W^y��\\U��k}\"�TJ]���D��Z�O��O�z�+^�֢}��>��+�xa��(��e/������-�py�&�K\0��0?�>]o����Vy����q�i�T�/.��G�uk���N	��zi�\0��弴a���{��:�|pW6_OZq�p3�WVm��t����͛wΈ�c�6JIb�\"�BQ��Jك�&�5E�t�᮪�C���\\U���s��5�>bS�PN�l�טCsn\Z�郸��\\�/�um0��]�׉ %�J[��	0�����??ǝ~��_nXR�x.�Y>�(���N��-oL������()����;�.ÿ@�[ǈ�\'ʽ���M��x{�Xy�j)�f�ڶSqv�R�G���0R!<<>�z+�C,��}C��?����Q*DIQ�,d\")� 8%|{��h���������뮻n���_��:޸q�ث_�������߻��ZYO\r`-Gk�{��Ѩ�	?��:��G�2�\"�/�\\{zz ���چ�I���$�F��!�\\�)��77;���}�:d�B8��:t�cg-�=��T\"�:\n�����|��E�v!�_s-T��o?{��yr���A�����𵗶��W\n�N#ug��#Dhc�\'�ѱr�y��	:����萻˙ASU�*�����y;��#��B$���X�TZ���iZ����.PĂ~yƨ���;orlllhݺu���G>�gϞO����ݱVO���&��o���K��t����bwEu�`��J��R�̙1��D	H�XF���\rK��[R���V��9�|�XcQ���&x׆<��}5`*�Z�{�\\��5��<�\\=ޱ�I]\'�\\J�S���}�����[��Z��E���5W}��8��_��\0�\n�(������H,��?d�a4:���h�ؒ��\nR���o�$�c�sXT^����Ԇ�A���Ɂ/���@f,l^�`�5����wΐs��;f��SGU��}�{߉^x�������߿�+���W~�W^|�Wnz:uI�l�p�����Ƙ�+�ʩ}}��{z��}}}=��C��舌h�FD��؛�tÌ��^���kA2Q�Z��!J(���|%NG2+[Ƣ�,��8��a�4{w���t���M��~�-��+y�{$��!sm3y���\0d��ڞ��L��a����[���1��8������Z�?�T��/?�N�r��@\0q��#퀈I�� ����s�� ����E	�4X\\��lA�Bx�y{t�xl�d\0>�%�ȇ��\0% ��� �`�sJgz�\Z�|P� �ɳ�������>������/���?��/�p�����>����?��o<��o��Yg�u�q�7�e���O~��_�������z���}���/��&�f�TXS.��ʕJ���O�|�IX�f�_����3���(�0:2� ���B�&�jY!�EM(����l˖���� �ȴ;��>\Zb\n����=�uK��on�^��\'�m7��v�!BQ�|�i��`����/=�&��0�[������\\�ӟ��΄���һ���H�!��ä�6`����)E�A)�m���sR~t�経������\'ƞW��F%�}Ǹ��C�{�	�,�n[H#z�q���OV-A])�r��w~�w����/���J�K.�w�%��۹s��y�{N������7�|��ߞ�x�����\nX�����a����J�V+�ff�����Ĕ���z�X�~���<\n����f�:DQ�hmR�Z�\"7�l!���{\n�S\r]\Zo9h�c�jda�@k	%R����Ɔ&\")!��@�H�cB{�@�X�R�|u)�y~�_0\0H� ���g��<�ů� ?f�exI�a���j&�%ѱ��\'��:���:X��3hj�SC �E�$�.�A���e�.mY\0?-��;�O#�1�8���0�<6�ߕ�q=���H�i!���0B5��u�q�5?�����hyz8��2\0�]5��$��`j��ݿo����\n�iaD\0�ê�U]5�Y; �-�*�Pi�U�΢>�_��+�+��篒̢B1[�S�\\���f+c�w��敻�{\Z�޺\'�ח���`!���t@J�<ֲ�v�A�8/0w��y`:ę4	��:.-��;�Y�8Ӯ������\Zz���V9V�.Ϋ�ԉ��燊b;2`,	�XB\nFj�2�pm�j3 �pĒ�	A�w���+�?`��j\0�m1�W@�j�����[0B{-!���t���\'Nݾ]Z������LS�t&�Fo_ejuO�ꏉ�q��h�if`���lv��<��ҡ�/�(ȥ��^��	<X��x֕��{��BWs1u|���|8�(�\\�(<���C����8���}�O;�ե�]r��4�\rn]n\Z�u�n�˶�B�r�B��<yO�b�Mg�v���n�,��} !�#\"DL!%\\���t��T=\0���p���M,��޽�Uo�9�*u���k�tƙ���22\"J%!����L4�g���3#ebE6vh%�-��-���ծH��Ó�d}��M���n\0�/zY�p�T�\0��q��8�mN�,�ma����R�P�uI>���PW�t�ð�C�i�H\Z���KrQjW�\\ ��9��X�?�#`���Q)��_R��C$p��g|ֺ�3�(X�CǕ��~��5/z�I\0�<����b���X\"�#b��7���rR�8���e�EƐYMsk2E��[�\\ݣ����\Zg�񛦖8cЯ��]��7�s����$C\n$���\Z�����*���h��͠.��yR0�ny���~~,�\0M�q�T!���!��U��~+簸\rx���!=��@6H;r���J�ן;�����Jbd��X\Z���K�u�o~~a{��av�������ZYOSJ��$�\0�\0�\r��웘��?55Q�SA����B	�Z.E�}ր������9hGЙE6�r�,.M���W��#vpւ��4��j��b$f�ĝ�C�Ȭk;���p]6h�dH�8\\h`:c�d�ɤ�E\Z.0�� �H ^�&�lc��ҡ���y����9n���j�`�gC��hi�\'B�w>0�[t�K*��>��>$��V�]�$��@)��RX�9��[RF\n<���B@���������LMM��eI?��he=���S.Y��L�`�]\0v��C�Zm���=x����MБ�a��Kt���G�?��Am���\Z��p�-(��Ds6�޾���8�k,�6ւ���&���b8b��@\Z�H죬<et��q���ex\0�C��ө��\r͈c0fǌ�ȃ.)<,��[p�]��܇J,�h��Q��PjB�ն��\"��\0���)(�-E�i�me}�o� ?�b�� ��H�c�#�8��Uf��\Z\",)�,BJ)\"�G� �5�V������oan��Z\'=+�je�����6�VWX�C�5�\n����j�>���Uc�qR����ǐD�S����B\\|γN;������I����j8�tb\\:�D}��4�f��zS=�΢�Ym�H���u�@I����fh�ik����_�$@8� ˮ]a�࿊�Jc˰�&Y���2ahjb;U9�$\'�e��<\rk�Q셢Y����-w@ߧ��n5�_V�%y\r���=�Jx\" }�F=1h$��a��9�R�N�!\0A�[	�6JIPR �$b%$���h%�2�W.W�V����\Z+[leM�����0��\0PP\n�jE�I����j;��� �/!iۆ��يS�ߴ���ھᚻL���5��N[F6���\\&F�{&7,$�i\Z�,��FE�� GD�A�TcB��:XȔdǏ+on\ZJ-�0�Hg��9hk��:�����j�������Q�/1C��/s^ǔ���\"�ۀ85\"�	C1�s�=�mD��@UP��Ý$qyJ�-?ᆠ���}��%<j�0���u3����!3�R�}t�|����[\'K)��o��#�X)\"p��W���\'I��\\��U)WvK)ӕ����&`�\\Vw�Մ��(�[�n����y۶�r~o__?Qg0��\"B$V�c��<���O�oba�D��,��Z���J� ҃-Q(O�����U�-K�oב�`-�j��4�N@a0x�W�O�q{�*���\"y~�\Zg,���@\0~��duF�\'��RI@��Q�p>r�e|Ǝ�2�P�����ᘃ܁������}>EG�0�+��.����������������e�Cf-�@a0�`Y�Z �Π�j����>%��+�H�6pI�Ix�q	���*�O^\\\\�ଽ���G+[me-���n�v Y�~}���}쌍��y����ł���z+]�hyЊ�\"�\'�����c�w�	�>}ˮ	�XmT��H.h�3	�-��y�gr�b�o1u�l�sY����.DZ����X�@���sZ�rH�<`0��`E��:c�W>�݂�7t�e}�@F�Š�W�G_��S���0?<�gR�q�-F��S�r�鶘��Y��A���k�jv�}xW�H\0�\"I�cљ��9�e��8�6���jA���XIv�4��f�΂�	A)!�$��JIo����e	!bY@�&�4KV�l��u���Qi��p�\r�[�lzqG�\'�<CIQޟ�\\{�� �� ��c�A�\0p��cן��������U=V�E\r�:e�h���Bqj�H��|]�]H��;�zf!8����XHD���a&�(�( V�L���1fق�����BkilH}�FXLX⇕G1�Ԯ�i��p\0gѩ�zI�(�r\0�\\����\r\"�mHmy3���>��l�	�N��u�=�iς�Ff�j_95�S�P���2�mUQ	U\"�-I���6�Lza�;����s�U�o�z?��[))p�I�\0\0��+��T�o�)u���nf~w��:���#�Gz|��\'s��s=ݏ]�����V�SX]�9����Z�o`�J�a�T�Jl\'��$\0��VX+��p`����[מ����3ͅyY()���Υ��p]̟�S�X?��m�>ӰT\"�FfK��X��J1�\\�M��[�:#�h4�1�Xh��شKk\r`C��XR����-/������g�m��T��Q���_�D��.t��/Qpn��9jUD~�Yԥr�`��l��,���y�bR���\0\0 \0IDAT��Ѣ���v>�/+�DN*ҍz����EZ������nྞ>E��瞀�� �8{�fܽs�(籖\r{cO�ƙ��6����6�#=�ў�X��x��H`�D����B�Z\\\\����mc��!��Q$�PA>���LH��֠~�����sVl�9��37����f���5-�R�B��!o��`Ϭ\Z���P�Ŧi=�y���qL/aU!���ed��hƌ���(KB_�+�#�Z��~J䰘�.�@��>B�e�Q!�uK8\'�#%0�I1�$���=���uH�p��4�-i\0nW+��]���+�Q�^Z30#���vG��Y�1bA!=z\nC��KE�ճ�4M�:��c�HI��{���\"�}�����\0;�i\n�.����\0\"\0H8����|4\0�p��#��c���:ʀ��j�6��L\'��Eq�Ǳ7t�!�r�΀�\\D��!Eb8(�E�c+��9�����]{��Ҧvͽ\r,T��kF{��l�q���P��E�>��$�fF=aL�\0�<V�0���`�H�C����3��6��]MxL�D�\0�]pY�>Q����<Ti����I��xI�O�B��k�:3�[5SW��H���ae@-ĵQ\0/fF5�F��gVPZO4kk�pL g���8���o��~��=�8��̧m=�}���|�+��(��(�1))!���옘]�;�y��Q�?�ɤ��\0�̵�DWO3`�jG�^�y��B\\R��.��9wEa��O		�zU4B+�d�\Z��2b�}��a�.6�w`�n���If�T:����E̟��wp�Z[0nvP/Q ����LX]��Č�t0��YF�k,���,ʰ�8�@M�켣沔PP�>���݀sb>���zwB�Fdh�1�H�<]Cw�T;\n⠌������YY?�\'�����FP.gp�����n��aI��r$0��h_1�\nQk���Db��;g��������(!�\0ܷk�Mq��>���/��o_�8�P,8��/b�Q�R���\0�M�^��t�\'\n0�{�\nX=��U��_�\"�gq�P*J��{\0��b�`�8D�&\n�(�Jx�MG~�W5k������t�����XAD)��̓�X�4Q�4�_ڒep�:�0%����F��d�^_�d>�����8Ì8��Y��4�M\r�,�\" S�Q�kO�v��LD���l\0kt�9Mq�+~���%�yމ٧s�:�\0��g�]�XJ�9(%CD����zۙ��>\n�.c�J=o	b�N+��l�Rl�2���u�\"g%ؒ3�Ձh�����*,!\0g��F{V�!�$a�Z��h�R\nq���=G�x�%�u������}�=xφ\r�X�j��DDK�r����h���/���F�� C��BZ����l�{^��u���DL��H�Z5�ְP�Qa��@Q�Ճ���l-��\'��\\�d�a�f�jd�琔 (�iSf|UL�EI:�2�ff�� m�`�U�|���0��+�v^��Bs#Af���+��%u<��Ȝ��E���]�Ѷ��m\\ڍ��u\00N�π�$AזA�pk+(_��+JV\"W���d���6���`���d��\0�Ǿ*�9�di��R���C��迾\0��}:�����S����6�\"��*�;�q/Y���\n����~��{�࿿�����mq\\�Bt׀xh��P]n��vop��gu6���,�``i��N�`S�����;��L,����N5Zp�r<2lc�쪝�I��d��5�hZF�\0Ib=IƄ��SHvH���E�thh�9��}��Zn[����|t=�\rd��ٶ84D!!m��Ԓ�����ib�_\n���t�x��������б��ZqH�I(�a�[�xp��D�kM�\Z�,9+�YI΂�l\r�H�[�ݍ�y|��{�c�����8�_���|�->���8.L)�z<�t$둸��>O�8���_��� r������7�����+�o�6\\,�(oq��)�8��+�>;o]A���`�5���)$������,T*B����gU	�\'`d [X`|v���V4հ��s{\n�CJ��@YH� yh\Z��E�IZ��0�pc�6��y;���ɶ��\n�(R\0�(H��v^\Z\"/�����Ԯ\n\"�#B=���h����r[�	BY��!����_�6R\0��X`11H��&�8՛��E,+�6�riq!u�f��I��.��BA7�`��\r\r`dh�(F$��ơ�Pg-�ٽ�#��RPJ��b!�L$��}}��k[�l�Y�j++�\'5��HUBq�����9��ێٰ�ף��rҝ����pH���O<HY�K�\0 UԎ�<��qu��DegiUYm{��Xȉ��Z<%��@M���N�:q�O�^ŔYJu#zx!�B�0%��%\"���$P�~0j��1�p��h�b:X��d�uޙ��I;O����k�E��7^��S�#��d��=����{B$%}��{��b޵E��\'�u&�t��<��N��9���C۩\"��J�Fʭ�\\�-f���30[��`\r��k�A�\\��~��\nj��^��b��X\\X\\⨓�Yc���Ÿ8Q(tEve�����\0њ�m|��ko9�����)�:U���\'���1Y�\"I���cbr�S�(��8�3Q(���:?�ʈ|n�#%uʹ�e9��~p_#�/cN2�:��DBn����<$�PL��H�X�\0)J�D5p\0\ZA�^�I�K�͞����#����&�;�*\"�|D%|�%��}L���_e�#�,E���G*��hj��YF�H���+�� ��vA����r�X�i9��� �Oo�)J�#72PiE�R�f�J,��Ď�,�\Z�I�&R����Ǟlf�� %�Y���9���c%���@D��f~�\\*O���P(�8�W�����X\0䍷�r�i���o����DQ,��茘�\0���1\Zss����ALLL`�V�־<�h������_Zw|4�r.�+�Ҏ!���Hn9}X��2�cG��4$Z� �5 B��CǬ)�A	�ݳ)��E�9!��A���@U�Z�E�9 �EMh��#,�����S�	`/���ôa0� �Q6�?\"��ʧ�\Z~�j)�/\n�$*��B�0ݴXH|d	��b���G\\� e��6@�y�M�kO��-7�����r�#���,�5#Z�q)�L��̖�ӒMƬ���}����E�J.Og�a��}ccvzb¨(��bQW�[.�3%�D�P��T*�r���J��P(�\0��:��{Zs��c7�t�O���3N��.JE0FCõZ\r3�3ؿ�ٻ�h4���(�E���R���~��P*¹���7��Z�N\r#&�!�vU�V�< .,(�w�B랔K�v,�!��ۇUk���V�;�Bk��6\0�!d��T�z�M8$Ϋ�9� /�̊��s��:o\r�A������ *`F�����H�祔 Ē�����3���@md��skm�iA!����=w-��X���M��H`��0T-���R\"��zM��XN��;��!�iuZ꩔ip�q�H);<� ����̴��W����+�`Μ�-�fu-�b��4���S�V���۷��X5��d�s+ke=��I�������v�۷�JZ	8��w���cc499�4K}7�RP*B���=_�R	�������m۶�\'xK�+�8�@��\rE��Ɗ|�$��@�uߴ-�k,�%:�����Ҟ\\��x�TVDM�hh�s�c�L(I�(&$��!�5�{d��� I����^�d]��F9�ڒ�H�O!c��=�u^���a}j������AZ�h[��q�M��(1Z�x��`{z�-�\n��Vj�\nV��y+Q�	6)۴Y*�Qqxh�r	g����ܿg�����㩩�@)���R*-��R�T�V��j�Z���i�������?�z��)���6[YG��-e����}����wY���&M97;KI�BJI>�Rm�;����q�8�195�k����p\'�A�}��`d\0-hkI1W��TY���Fr�AM\'�Иh\nh&>���F��9>����J$I>4��Bb}t@�rhPk$�&A�9�P�E�x�ܻܿ�خfb�*�N���\"���ʑ�-f�~�9,�=��S��t��%\rn�Ҡ�~!��Z��}����\0�K\n�zb�+�Tl%�Z��a�ȊXfMl-;�l2ش�$\\����Vq�ɛ����+�\'lZ��c�������>p�������LJ)u�I�XlV*�ZOOO-�J���J%\r\0����je-��Ҵ9�l���z�Y�G���H\0uؒ��(��h���7�0�uͷ���)�l�$@r�*}��H��\0#�Z]��}Rn�Z�PO�ܝ�Δ��dMPf��J�6��\r�x��<�;T����ͧhi�\'%�I����4���+�ˑA�ڹ`��>U���=�O��N�7���|1u^�@޹BP�\0�A=phh��v��hj�6�BCaV\\r���������C���[/�؝�����3M��2���B\'�����&�u�d�gnzN�����<h��c;�����1��q�3b\0�\0�S����{����/��J����驟}�ٯٷo�_�EǱ�{����Á��4P���g߲�X����ю�h�G��#=�p��H�\\��tl�,i�z�t�=zj��]�#Cw\r�]X�q�xO\"�@�T0!8����Tغ���x04�\0\\6�έ�u�\0ń�UN���g�=���&#Ւk����A3���U�q�Pe�8<�{gZ���H3#\0�2k\0km�J=/\\kjĊ+��I�\ns\0C�_.�E���y\"��D�YA�`�Zc�#5�<H�ַ�$�Ү��@Q��Te�����o�A%x�E�`�`��-cIݩBR�H����}�!���c�į�qwb-��l�/�澙�~}����;�Jl�T���§�\\�!�9<���b�����\\�կ~�y����\0��׷P�V��j�\0�r9���)<\\/�c��y����j�H�}40y\"��\'��G�|�����au�����3�S��4W����*\"z�㜈\0ck��\r	\"LOMᆛn\08����B��]������rr�U���C��&M������b�ƙ\r��Y;�̱�ro�<[,	u`NЁ�2�A�\0�pa�4��gc���D[H\"T�>ݍ��G�@m\'Q/2�������]�EԖ8x�{�W�5ޭ5�?� ��!�\"x7Q���z�\n%�\0ht�\'PL��l��2�4\0O\0/�$��0t�\0�S*�-ƪIAޟ!���i�\0�Z�znvn<���B��\0����\0.�J��R��\0P(L�vyd�X6�\0�8�S����WRেtS?0��������|!٩4�?����������}��o��N9��\0� LOM��[nB��8e۩�M�׹V+����ީ�2���!!O���u����񉺪5R�see6���K=��Je��Li�,��|�f4� a�<���D6Q\0&���a���X@HBQ	 es\rV.�ls^|8c����4���i�`��c�Gi� \0U�-J�)*������B����_\0�8�k�������.mtk5\0�\nѠD�֪\rX��):������*�6�r��\0����\0���o\n�f͚�朕�/`=U��h{c=\'�G{�\n�=5��O�CU����ĭ�W\r�V�V��͇6��xjzڍ=�������Y�Nnjj\Z�}}�-�n	.����m��\Z��N��\"(�i�w:@;��g�q��f�Ze��H�`�ّEg�k-�����\\\n��R���$������Ly��L<[�8��na�J$a���f:��&K�ȃZp��&9p>�!�Gc�B��:i#u2=�k؂Ƌ�ߕ������gE�b\"QP�ޒ��j�K�62Jĳ)\0��-�&�����.��w��럿1������x�^%���{�sO>fI�|��}عw�ݸ���}������#���*�ʤ���!�j�@\0h�Z�-�J���H�GJk�<���å��|D߫������O�K�^����	��Q~\'�G{�����g���7�]���J)�R8f�f��&&����$����V�e�16�`��������g�>�a�j!.�P,\"�cT*�|�)�z��(����$�O�ii�iu\r�3BC44�i��H��q�2m:9S��JTT�#%cW^SAyD�l.��3ӥ���؁q195M3����+����c���� ��I�	��7���j�I\n�v�w�������zYCn�[�H�B�JL(E�˱�J9v�rQ�T��D���/�Lk�~�z��t�w����VękYe̺�G&� �V)\"��-7>�R]Z+)r�k����Q��nL7s�Ɨ�����R�uGTO$�z�Q��ؤ+���e�^��(˄�5�,�������뵺���M�ٙ���lE�9��8�4|5\0���,��q�B�\\Z�~ݺ>� �Z��;\Z[O8����Ut]Rn�BmL���[�ȹb���b�����Q�㉪ϵ��(.T��A*�+�R�ą�HG�I\04X��\Zm|�d�O.\rQu�V۳�Jxǹ�C�-!�}D�i׶+ΏW��z\n�+�@�q��8����4��I\n�9h�0�s��Yy�R�L�i�e��Ȓ�d�5R��H�*nBs��oyE��_�/��s�\'��\0�X,��X��je��G�t�6,�ܹ�g��g\'�&����(|��@^���Un��5`&��w���z�T޺f횁�af��}c�Zc��z�zϥ��K�������?�����I�+��V��%�-�29�DmR���QV-VgEEI@i�`�5SM�q����yi�	�NT�r�	 ���A�� rP���2)�D���U���=~t|�(�Z��\\����eaj�L+���ˏ�v������%��;�SIN�l*Y���d��!A�hYT���n�:l9��u���(�����{�]�b6������(��T/�0�{��;�7���C�`��F\0���ʞ�{f�B��W,l[�v�p7�0?����Y��BA6�J�+�3��C�Ij����S�à`�3���l֜1i�����F@�d0�3Z�L�Lk�L��B\0��K85t8\'���ݧ@�{1i!�$򴫠\"���#��8r*V����6,���d&�][��;�~Il�Hb#���vg7KF+���lT��\ZuGSK�Jt@��h��\rط���̌5�ם<951\'��I��i��|�Ҷ�t����L�\0`1�Zq��@O�����i3|���W>p�M)({�s���u�׎�	�u��{B��8f�f�����E-� �PE�l�&zpy�!�����Kv\\-YSVZ�4�I����z��b��L&���\"*e�¢�p�g,im�6���d�)6�6]��uĤRD���PJr$K%YEҁ�s$���uG6M�^�����-���6��\n����c����ҷ��0�)B�}�2r��?۫C�2)����0T;��mE~�X�6h�/c�ȇ~�ir�b�����\n!���=U�+����e1r]gz�Y�RU]U������]�#���$J��x�g#d\0Af���x`=�%y\Z O��2H2��<(ck�/i-�(��N6��/�]�]뭻�s�pϭ:UlI��Q����Z�xoUݯ��?���`�_-+eNM�wTY@^�\'5��������R�j\0�\\�r=\" ���_�܁Ƀ�u�9i@�kk�J`��>���\0\\�B�僒�����N��=����^?�B���\0JEds�N,�*V@݋�b4f������v	�]I]�0��$JH\"�$R(b��\"	�Q\0�$��Q��J�B)A�PT�\n2�!#	K� %��F!U@%*,@P�b���C�TC�E(�C�X��_7$����?\r��Q�ۻ��}r|�����Tn�_�:��-]`��Q���5�&��\"\rTw����Q���\'\0�5�J�Q�\n��Ѐ�ׯ��\\�&:~\'���ȉ�:�O���Y)45�E!�8��}�.\0�h����Ls�xJq�Ԇx���\Z�T T�6^�$aRr����1#1�4��	%�2�4ӫ�\0\0IDAT8��QF)a$�N@�^04���J)@\0JJ��TJ(\"c���*����%��Ĉ( � JI�$ cqT\0�j�*Υ�3T)8I���.���@5��~\0���\Z�8�о`���2Ƒ�@AQ���)a�Bah�����]�V�oT���JYV�C,454�9�\na�:�ǈ�?;�\0�̭9���_��}�=2��7\rqa�Z��]����p�d<Col�M���6Up(�P�(tH2b�)	*�$$Q��PP%a+B,=�X�A(��I(QD3��E��\"}ī;Bi����H�TB�$UJ�n�p����W+B�.���/�q�[���ǳs����c\0\0_��^�<N��?4��!N��i�O�[i0��9GG�������\\��W\0���L�Eq<^*��� ��������P\Z�]�,~���R�z��``	��mv��׈v\\,,,���ѳA������u���R��\\����D���X�J��r�0,�&�6S�4x�T�\n$\" \\7C�\n{)��%�҈���w)B�I��H�K�>���eZ�����W�$Z\rK���H�\0��7V;DIN��O}n���y(����������U&���f�ģ�x��l�i���Yͨ�LN`f~�X�c�����-��������2���R@���4e_��YX���ҏ��#�A�U�cxw������ؖ�0�L\r�H�\"\0\'�\Z����zv6�[����Ǒ���Oߵ�\"��p�b	�e�������%�X���!���(�*����$l(X\n`B����$OF�+��,+�ԝ+@[3�9@������� �nz���	\Z&@�姄@��>�\"�����g=��&`��|)a�:No���Dꠊ�?0��V���:�R�<A���U�D���RO�>0q3s�n+����\r���7<�1��\"�q��u7)�oX� ӛV�=Z��y�R�~��磵�j�����G��iY.�\"�]qC�@I��l��a�*�T!�\0�*XD��E$  .�|�C��\r�H}�t٫��Fm�ؓ�։9�^����\0g��yIz���D��\0e\0�m�H�Т�\n 4@)����>b����/���a��	<�Ce�\0�t|���������(e`�.Z����(���*�8�/���w!5\Z`\ry������6�f*:��(\nϼ��`sc��{���G��׾��P�h%\rв;2���	=վ�]�Ew�(8T�g:5�-KR�����+8�w\'�ka�V��;\05E��=ͽ4I�K�&��̬�L2�\n`\re9EoXE\nP&`�Lu��̅[x��I\0�٫���{i�>sdR׫f\0\0�\'\'�o������P�ױ�^5N�d?���Wp��K�TV0::��P�|��c	����@J����E,�*׻���z��\']���~fii���m���e�Op�SfƐh�\\\0\0e\0c\0v0^,�����\'��o��/�u��C��9���(d���E�&�Wb� V���@���h�=�kM�j[عc��wϟ_�D[\"Q�-�)o�Ԁ�NgކM�\0�V�g���ޖ�|t@�n^��Q�sAM�FxpW�]FB�3�F��j��(��Xjm�l���7��˿��-����e����cl\'*�U�Aq�P\n��0��sR����íB�\n��,���OJ�������������:u���\r$}�m����ճ�\'x\0ʨi�ia_����q�ȡÔB����/��=~F�rQ	c������H\n�!p�xl��66V�Xmbr���f\0�Xf�t)�ғ��T�6�R���YU7�3�T��S��F��R���7z�u�GH��g	댣m?#�h4\0cL���ˍ�MB@�v��~�b7���z��TVẮ���xD)��ލ��_/�J��K���d�.q\"���N�:��9Á�P�I��?��y\rֳ$\0�կ����R:�\nB�=�\0��LC��Y����J]��6����a�Ɂ�X��g_<�?�w������!��P��ۨ4mbL�ꥂP����S��*M�V��;�	d�R��nj,D�v��N�C&;P���pa~QPJ��谝���{1��`P���PJ�T*#��#��d�^[nԛ7���С�uWS�����b��|�駟~�`T�X�dJ�ݾP\r�q�0�]?������O<���|����\rڝSJ	�턥쥊�sg,%��P�biy/��VVV�*�<<�\\�\0J9�|�+�ƗN���:��L5�kYR3+e�&*��E��D��^K�d\\�az���R�A�N�C�k#H!@(ItU�+B k��W]�v�ՍX)E��Rj�C���m;�35�w�Y�m��������V�\n�|�\\.��Ţ_(��e4cXYlV��W^��\'ON�B\"6o��F�I-��Cf�S�j�<y�;v� c��a��������q��$��TEyJ!)A������m�!��&�V�!��m����*K����ocn����;�Ne��eدw�p)Cd9���^e��8aN)1��X?�8�Z��ZmQB��1p��(��F��h�\Z�Z�)���B�!x�v�v�ް�T���a�T*���@HU*��V�u=�/T�����C�q��+;7��Y�\0�\rV�HD�� �z��;��ҔK�\0�w�����;��t������VQ�	O� ���U�N�.����đ�d\"���-Mv���_�w�z���O��ĕ�i��0ˆ���8GOYE�L/�R�\"F�R�(��Q��Cb��b��2!�UƔi�[M4\ZuͤX�p����t:^����N��\Z\ZJ��$�\"+�\"\'C7�\"��8��HI��R�(8Cᵚ��N\'���緊ŢW(�t:NƬ���l����3\0���kO?��S�N��4X�fiJ(p�m:�<����?<���7�?r���)�$�$�SIJ��?ETR���JB\n������;�@���Y�H$��R&^�G{ҿ=|�0?y��1�۳��>�,��&Zq_\\ZZ��~��s���66�!M�E�ߣN\0Г\'O�w����4\'J���2��S	�M�z\n����p�2ν�6���R�����R�d�RP��.���~��3���{&�?)eT�iRO��q0]�mܲ�)e�2�]š\"\Z�6Z��6���˪W8����yܸ1�b�F��Qݨ��W�q��b)�6m}�QBb	TB\"%��w�ޝ?|�Pibb�s�͍���7�_�q��M]wH)}`�B�q�4��*�@Vd�I��}�{h\Z\"D�]8\n|�9+`=����QBQB�\n�t\Z�5�HrB���T�G ����^}�u��M\nj��GQH-��Ά��`�u\'�$�r� $��8c\Z�������>J��v6�6P,phrk�����2��MK�	�9��:��9����J}����j�\"fSJ���D��`��Vҷ���U�j5�mY��|���so���.�Bi\n��\nOVY��^��\r�z����)Xݫ����ի�v���sG���|�ضMc	�R��E��4�sv��\nB	T�U�|�W�T*(��P�V�W��zEbǎ1{xd8_(r�qNe<!�43��i��.j��6�,7�\\2�5`�l+,�67kX\\��P.��Ǐ�v8����[��Q\r���_�m쎢��J�b��XC\"�kh�2ٕ	,����4�JVY���Z��̙W�Yo{^g�`V��biVY���`�p<�E��w[ú�뗧_�o޺�ٻO;zT�8�ٷg/a��3F(M�*�h��Q�q� �_��/�T\ZB��Ξ[�ysz�7?7��./��ᑑ�c�R�\\*��9��;�$�Kp�c<*��-�]�c<��8������F���&V+��{��Q�V��`�2��qN,�e.�.4\Z�E$�a���1h�	,im���d��y�<�DE�(�Zۀ��똁U�\Z�A�`Sr������A\Z�V=��pvf���ͩk׮�\'N�Ç��=�{��	�\"}�i�I�ʫ����^��9\0ȩS�߹x��>}�����RY����GGG��G�K�#å;w���R>��;�1�g�kS��$����Qf%�������̜Z^\\&c�׶����&��D�k��U}��K�	ep�����f��6k\0�gP��/wtj�h��C�򚡷���?DY�*�;-��=�����X��j5x��#�z����jvv������s�.��ypƻ�bGx����~�|߇]\ZR���o�{���r@�Ju�I�=�}��-//����9Ji�s�ڶ�ʥ�ccC�#��R��+\r9�r�)N�X��#�p�%�P�i��X\\\\��R�3\"����<����X�D %�v�}����ҋ�>��Q��ٳ��vޥ>��Jb=q.G�m�ʹ��j�65�,�x/��Ā���^���-ߓR�	1�9B<�����������8��݇];�뺠���̌z������*�墪���K.]k4\Z�\0��q�Ҭ$�Z�i�)�+�t�0t�0�[�����l��Y�e9�kێ�ؖ�X�cY��:�#Åѱ��<���b>��e;OU�f���x���(\n���S�)�\0�p������ݴ����?`��bX�x�|Y�h�(} ���� ����b���{u	���k���Mlnn`��]P\n�?zo����r��w�gf��,/OX�[e�b�p�flV�i��l�ӿ�p�p]w�W�|�e����X\\Z��?��r[r+Y��k���t�K\0n��޽{m�<�͹�w�0}����z\Z�E�p�V��hnml�|xd���qB��G-t\'17�\r�2µk�x��o�3)e���rszj�2�e��\0X�u�z�h�`�@�d�7x�\r<�E��6��~{sccxr��0�uYV��JeG���vA?�2,j�L�4�q�����л5���$R���0��>��WSB	 ��s��+�obb��������;��;��PL��+�����8`��͍�����e�Ԓ�U\0UͮZ���L�ҍ\Z�4�F��m�oE\0;\0����G?���Cš����X]]�䁃��B�Vx��k	b�&e�\\�466F766��|�_�,����^eXi\r%\0И�[�>7�X�2z��G���#�?w`r�0%��!�}_I)I�kW����w:��m��i�+����R%:p}p3WިfY)`\0���fW��f���=�9g��A�����*v��\r�O���\0K酽�nY��gv�|y||����0�9�,��`��~�2e���x����SS��qU�<������l�9�,W��P��3͍���ꛛ��ٗ��n��6X�1�L3AS�k�xS%���M����ض{����B!�ڶ\r˶@���عc�]�;!��\r�� ��J���ϝ����t\r����-e��\'�\Z���a�oݚ]�v��t��Z��Q�\\r]�u�^��.������ʯ��U�z��;��6\0�7��]�̴�Hٗ�l6ٱcGv��3��[	�r�A���\n���pqH�)y��X�H)!��B�y��~�͗������E`}%\rPHWƼN\'hܺ5�r��;S�V{�2Z_XX�9w��3R�E��`���|M�v��r]��8��bq���#pǲl�,�u1\\QRI�X��h�[h6���kjsk��تo��n�����^z�������׌�Vd_�,�� ���3�HSY��^{I�6��\r\r�V��A�Mj��g�FO�Q.է\"��Q$�4�ڽ�?��?������(�]�r��B����*��u��m�a�x�3�\\�!�� ��ɭ��W���Ǐ�}�\r\r���Aư�������g����uz�D����Z�T��Z[��a>�v�`\Z��U]��LOM_?~����\'�\\���㥗Oc��Al�R�� �s��p]��01�X\\�T^�����z��Y�LYJx���#i\n�P��ʠk���Zb.�+��R�j4Z���(��%�9B�������<a��p@8���˲�-�,�Ǖ����������HR���\n=��a}��Z��\0ؾk��Rl�����:�������7�/�ۻo\\J�/]���SSĶ�ĥ^a	%RJ�	��-d\\[^^9��~�׮]�Fϛ�lH��U`}J�Kl�d8&��8����N7Xo���_��_�ܭ�[�.\\B�0�E~��t6�`m=���ߩlmmUV�W���7+A�62du�,~�����I��ۍ,-s;����WWVV����4Z��f����<�Q;������C�\'v\nT����\"�,>4в0��8N9�tJ�鎰���v����%����H�ߴ�0m�NW4ͱZ�B�A1��K�f�[<{>�Hkl�<#4@l;;�\'�dV/Yd+���}l��sy�\rPe���i�k\\XP��\0\0\0\0IEND�B`�','');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'qfacture-testing'
--
DELIMITER ;;
DELIMITER ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-06-05 14:45:59

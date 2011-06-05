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
  `name` varchar(255) NOT NULL COMMENT 'DÃ©signation de l''article',
  `price` decimal(10,2) NOT NULL COMMENT 'Prix unitaire',
  `comment` text NOT NULL COMMENT 'BrÃ¨ve description',
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
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil auquel est rattachÃ© ce client',
  `name` varchar(255) NOT NULL COMMENT 'Nom du client',
  `address` varchar(255) default NULL COMMENT 'Adresse',
  `complement` varchar(255) default NULL COMMENT 'ComplÃ©ment d''adresse',
  `zip` varchar(5) default NULL COMMENT 'Code postal',
  `city` varchar(255) NOT NULL COMMENT 'Ville',
  `phone` varchar(14) default NULL COMMENT 'TÃ©lÃ©phone',
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
INSERT INTO `client` VALUES (2,1,'KÃ©vin Gomez','35 rue de vichy','','63360','Gerzat','0698568827','contact@kevingomez.fr');
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
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil ayant crÃ©Ã© cette facture',
  `c_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du client',
  `tr_ID` tinyint(3) unsigned NOT NULL COMMENT 'Mode de rÃ¨glement',
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
  `name` varchar(255) NOT NULL COMMENT 'DÃ©signation de l''article',
  `quantity` smallint(5) unsigned default NULL COMMENT 'QuantitÃ©',
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
INSERT INTO `template` VALUES (1,1,'html','ThÃ¨me par dÃ©faut','<html>\r\n<head>\r\n	<style type=\"text/css\">\r\n	/* GENERAL --------------------------------------------------------*/\r\n\r\n	* {\r\n		margin: 0;\r\n		padding: 0;\r\n	}\r\n\r\n	body {\r\n		background: #fff;\r\n		color: #393939;\r\n		font-family: Arial;\r\n	}\r\n\r\n	img {\r\n		border: 0;\r\n	}\r\n\r\n	p {\r\n		margin: 0px;\r\n		padding: 0px;\r\n	}\r\n\r\n	/** logo **/\r\n\r\n	#page-top-outer {\r\n		background: url(images/top_bg.jpg) top center repeat-x;\r\n		border-bottom: 1px solid #7e7e7e;\r\n		height: 92px;\r\n	}\r\n\r\n	#logo {\r\n		float: left;\r\n		margin: 45px 0 0 45px;\r\n	}\r\n\r\n	#logo h1 {\r\n		color: white;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 30px;\r\n	}\r\n\r\n	/** Contenu **/\r\n\r\n	#content h1 {\r\n		margin-bottom: 10px;\r\n	}\r\n\r\n	#content {\r\n		color: #333;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 12px;\r\n		line-height: 18px;\r\n		padding-top: 2em;\r\n		padding-left: 4em;\r\n		padding-right: 4em;\r\n	}\r\n\r\n	/** Tableaux **/\r\n\r\n	table {\r\n		border-collapse: collapse;\r\n		margin: 10px 0;\r\n	}\r\n\r\n	th {\r\n		height: 50px;\r\n		padding-left: 10px;\r\n		padding-right: 45px;\r\n	}\r\n\r\n	td {\r\n		border: 1px solid #D2D2D2;\r\n		padding: 10px;\r\n	}\r\n\r\n	/* DÃ©tails d\'une facture */\r\n\r\n	.align_left {\r\n		text-align: left;\r\n	}\r\n\r\n	#invoice_mentions {\r\n		margin-top: 20px;\r\n	}\r\n\r\n	#invoice_right_part {\r\n		text-align: left;\r\n		float: right;\r\n		margin-top: -120px;\r\n	}\r\n\r\n	#invoice_customer_name  {\r\n		font-weight: bold;\r\n	}\r\n\r\n	#invoice_products {\r\n		text-align: right;\r\n		width: 100%;\r\n		margin-top: 30px;\r\n	}\r\n\r\n	#invoice_products tfoot td {\r\n		border: none;\r\n	}\r\n	\r\n	#invoice_compagny_infos {\r\n		text-align: center;\r\n	}\r\n	</style>\r\n</head>\r\n<body>\r\n<div id=\"content\">\r\n	<div id=\"invoice_compagny_logo\"><img src=\"{% logo_url %}\" alt=\"\" /></div>\r\n\r\n	<p id=\"invoice_compagny_adress\">\r\n		{% ae_name %}<br />\r\n		{% ae_address %}<br />\r\n		{% ae_zip %} {% ae_city %}\r\n	</p>\r\n	\r\n\r\n	<p id=\"invoice_mentions\">\r\n		NÂ° SIREN : {% siren %}<br />\r\n		DispensÃ© dâ€™immatriculation au registre<br />\r\n		du commerce et des sociÃ©tÃ©s (RCS) et<br />\r\n		au rÃ©pertoire des mÃ©tiers (RM)\r\n	</p>\r\n	\r\n	<div id=\"invoice_right_part\">\r\n		<p id=\"invoice_customer\">\r\n			<span id=\"invoice_customer_name\">{% customer_name %}</span><br />\r\n			{% customer_address %} {% customer_address2 %}<br />\r\n			{% customer_zip %} {% customer_city %}\r\n		</p>\r\n\r\n		<p id=\"invoice_date\">\r\n			{% invoice_date %}\r\n		</p>\r\n	</div>\r\n\r\n	<span id=\"invoice_number\">Facture nÂ°{% ref %}</span>\r\n	\r\n	<p id=\"invoice_desc\">\r\n		{% invoice_comment %}\r\n	</p>\r\n	\r\n	<table id=\"invoice_products\">\r\n		<thead>\r\n			<tr>\r\n				<th class=\"align_left\">DÃ©signation</th>\r\n				<th>Prix unitaire</th>\r\n				<th>QuantitÃ©</th>\r\n				<th>Montant (EUR)</th>\r\n			</tr>\r\n		</thead>\r\n\r\n		<tbody>\r\n			{% product_line %}\r\n			<tr>\r\n				<td class=\"align_left\">{% designation %}</td>\r\n				<td>{% prix_unitaire %}</td>\r\n				<td>{% quantite %}</td>\r\n				<td>{% montant %}</td>\r\n			</tr>\r\n			{% product_line %}\r\n		</tbody>\r\n\r\n		<tfoot>\r\n			<tr>\r\n				<td class=\"align_left\" colspan=\"2\">Total HT</td>\r\n				<td colspan=\"2\">{% invoice_amount %}</td>\r\n			</tr>\r\n			<tr>\r\n				<td class=\"align_left\" colspan=\"3\">TVA non applicable, art. 293 B du CGI</td>\r\n			</tr>\r\n		</tfoot>\r\n	</table>\r\n\r\n	<p>\r\n		Ã€ rÃ©gler par chÃ¨que ou par virement bancaire :\r\n	</p>\r\n\r\n	<table>\r\n		<tbody>\r\n			<tr>\r\n				<td>Code banque</td>\r\n				<td>Code guichet</td>\r\n				<td>NÂ° de compte</td>\r\n				<td>ClÃ© RIB</td>\r\n			</tr>\r\n			<tr>\r\n				<td>12222</td>\r\n				<td>22222</td>\r\n				<td>22222222222</td>\r\n				<td>22</td>\r\n			</tr>\r\n			<tr>\r\n				<td>IBAN NÂ°</td>\r\n				<td colspan=\"3\">FR22 2222 2222 2222 2222 2222 222</td>\r\n			</tr>\r\n			<tr>\r\n				<td>Code BIC</td>\r\n				<td colspan=\"3\">Code bic</td>\r\n			</tr>\r\n		</tbody>\r\n	</table>\r\n\r\n	<p id=\"invoice_compagny_infos\">\r\n		{% ae_name %} â€“ {% ae_address %} â€“ {% ae_zip %} {% ae_city %}<br />\r\n		Telephone : {% ae_tel %} â€“ Site Internet : {% ae_web %} â€“ E-mail : {% ae_mail %}<br />\r\n		NÂ° SIREN : {% siren %} â€“ Code APE 6201Z\r\n	</p>\r\n</div>\r\n</body>\r\n</html>');
/*!40000 ALTER TABLE `template` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `types_documents`
--

DROP TABLE IF EXISTS `types_documents`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `types_documents` (
  `tdID` tinyint(3) unsigned NOT NULL auto_increment COMMENT 'ID du type de rÃ¨glement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de rÃ¨glement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de rÃ¨glement',
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
  `trID` tinyint(3) unsigned NOT NULL auto_increment COMMENT 'ID du type de rÃ¨glement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de rÃ¨glement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de rÃ¨glement',
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
INSERT INTO `types_reglements` VALUES (1,1,'EspÃ¨ces'),(2,1,'ChÃ¨que'),(3,1,'Virement');
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
  `te_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du template utilisÃ©',
  `name` varchar(255) default NULL COMMENT 'Nom de l''utilisateur',
  `address` varchar(255) default NULL COMMENT 'Adresse ligne 1',
  `complement` varchar(255) default NULL COMMENT 'ComplÃ©ment d''adresse',
  `zip` varchar(5) default NULL COMMENT 'Code postal',
  `city` varchar(255) default NULL COMMENT 'Ville',
  `mail` varchar(255) default NULL COMMENT 'Adresse mail',
  `phone` varchar(14) default NULL COMMENT 'TÃ©lÃ©phone',
  `siret` varchar(17) default NULL,
  `website` varchar(255) default NULL COMMENT 'Site web',
  `logo` blob COMMENT 'logo',
  `fac_reference_format` varchar(255) default NULL COMMENT 'Format des rÃ©fÃ©rences des factures',
  PRIMARY KEY  (`uID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Utilisateurs de Qfacture';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,1,'Julien PECQUEUR','30 rue Charles LabbÃ©','APPT 10','80000','AMIENS','jpec@julienpecqueur.com','0649869072','527 958 821 00011','http://www.julienpecqueur.com','‰PNG\r\n\Z\n\0\0\0\rIHDR\0\0,\0\0\0–\0\0\0d[µÒ\0\0\0sRGB\0®Îé\0\0\0bKGD\0ÿ\0ÿ\0ÿ ½§“\0\0\0	pHYs\0\0\0\0\0šœ\0\0\0tIMEÛ\n;7•—\0\0\0iTXtComment\0\0\0\0\0Created with GIMPd.e\0\0 \0IDATxÚì½y´¥wY&ú¼¿áû¾=¡ªNU%©$•\"			„P”1Pe\nƒ6İŠÜ¾(qˆmA×‚Qhˆ—«}A{İ¥\\ÛÕ}mmÔvdğ¶f¢„L•¤RÃ©:Ó¾á7¼÷÷÷í½«bdÊşe}Ùûìsöxê{Îó>¿ç}^Â#r1M¯¾	rı&\0\0º\0®N~HnİÂaàĞ˜ŞgØŸ]ÇÅÀ¾£s_Ï­çqûìëÁÜ^¿ó·\0ıKå¶_¾ş€?\0€/Î~o»b,Öb=‚=â\0j¤®H—k k\0Œ òNĞ	Êho®g ú4hß> ŞœŞõÖÜg¸;]=U¾Æzº¾*à³åÁF®Ÿ¬ÁR®.\0¯Và/\rˆ­\'°jìğZ\0Øb-\0ë‘Rs\0uèNïµ\0Õ‚ÓJÂ\Z0ØÕÔĞê*Pï€ÜHÏéÙg¸”.wæÖöÁØ–Ë|	¼¹	dœ{ğ)\0¹ç\rxk·€X·Ÿhl¾ó¸?\0ÖÁğZ¬`}»Õ“:œJ¼µ“Pój«µ²	ª-hÀ©«ANƒœc× B\\	Bğ%(W IzªîY¯ÄtÀuLÀ2l\\E°	àª¶lxÀ™=8wà­U´NnØ`¾s|Ë¥`Ì3¯p-Ö°¾\rÀê,Fux®Ü+; Áª¾\0ÔA5; ¼Õ3P&ƒòJÀ¨½ÔµÜ–¥ÛNŸÚÎ]é3‚Õ!X£ÕdÉÃA)Lìf&d¹nŠnz{–š‰ƒ¯\rBÍ`3×°‰jÎ!Úx²	îv[\0+Çˆy\r>µ¼²…xÏÜ™®e\\ĞZ¬`}ËÕ5k Ñ\04Ï¦¶†P+ç²Ô(‡ÊJ(§AÖBé\Z*8)®ìèô¤kJ¿ì\'“}›;nß°löÖuØí#V‰ã\n=Ñc¢.Æ3X{KÔ€Ñ°â1;Æ¨íN¦N:æx§ß¹¯·Ô9¬İ^Ş·:vŒ&zÄšÁÁ!†±(«-pÓAì×ˆC^\Z#ÖÄ–u­ïE¼e¸\0®ÅZ\0Ö·&P¥Òïš5ĞŞu¨á›Z¹\0´3‚Ê([Béª²PÚÈÑqĞ.Â×vóÈöÚ©õ‹Ç£æ1ÎÇGs‡4a\r@‡\"2²&’\"ˆ€0M\0˜–\0ÃGÆÄE&‚ËjEGğFßª#İÂ~i÷Röåsö÷oëíßsßĞqå©ğXB1xÄÂ!†¢kë\nq©¸åÁÃ!b§ß3¯­!¡s-€k±€õÍ\rV×¬F·ÖÎ‡Ú\ZAí)@ÃT§•—PYe2(vĞÚBu,tf ûUİ½çî­ë;Wî›\'Õ.^ÁĞJaˆ¤š!\0„\01A‚!@## 	V]„ÀhBG@SÄÄE4áCäA†	çÖÜºo¥øÄş½½Ï¼lß\'ê|ìûğaˆ\"Yß 65bİAÂÊD×ú:b§èŒk±€õMVoš¾~uø\\P¹\nZ[ƒ\Z :C¨a*Ï¡¨¶ªë =ÃäzE#¯Ÿ:wıäğª­ú;wJuø@\0‘HA)Ê4A+B	ŠJ·`Òí@¥”™aÀ¨#£@ŒŒ#˜\nb\"ƒ8\"#Æ¨‰\\»À!¢î:±k`?³{9ûÿÎ=oùSkÎ½ç´Gå|Ù À\"8‡ÈB]#–%âhˆØãZ¿ñ–UD\0X°­ÅZ\0Ö7¨8½ê9Vµ¾µ¶µ7mu¡t­´Í ÈCwshaúL¦7>¾}ğ®{7®95ôO+?:ËPJ‘V0JÁ\ZBn”\"8&EPŠ@ ¢éGÇ©Œ#W@ˆ¥g¸È`fpºŒs—1Fpd(fXD€#4#ˆ	¼†İ\\İµ§oÿöÜóúµzhï—¢é|ïü¤Fè„Ğ nX„=B[*®¯#®­!NÙÖMàÙo{Z‹µ\0¬¯ù7\'¨g«Ğ9hêB÷=4\' ê°ªó£wœ¾lc}øœÓ#ÿŒšeYk4ŒVPZ”¡c<<†¤	 ZÀ¢Ä²Ú39Æ7‘1+fÄ¨^‘#bĞR,ÌË¹Í ¢£ä6ï#Ê&@Å…:2èÙ\\tîÒ_œûØón	6¯F;\\T#ŒOúÄ“ÛM†ğ Âü‚m-Ö°¾ş`Õ²ª:å5´@«zÙC#‡^.`\n†Õº.NÜ±yèøñáµ“Iı!âQA)c\"c4\"iDE€ÒPJ¡k	F+L\"!3Â®\"HŒ”\"hJ€5{°\n8U	İj\"#²”‘#bˆˆÌS°Š1Â0Ã…„qÅÀ‰eu#ƒÜæ|D1tî_]*>pÎÁ__xù¹_Üöy9là›Ş<Âf†à†ƒâğóˆë½³ØÖ´kX_?°Ú»ur\r*k ;=(êAw·`¸€L^#ÛİA¶±1\\;zû‰k¶wêâ•Jë<(M¤XiD­¡´‚6\nFË±«–Å¤iB$Ñ¬8	î\"°GPÚQŒj†c†o·™A	¼Ú2PJÆˆ!F¨Ã‡ €å#bĞŠ!Â‚‘#ø\0ç‚ ]\'S·ØÓù³G]²÷Oí9ûî)#j\\Ù \r?Ñğõ1Ä …mí]G¼s|Ë*âùh-Ö°> €k¡®OV…Á\njhxhô’Î0¶€évBÓùû8ñØíã;/®_kZ­¡P“Ff4”Ñ€Ö(2n¦`‚Ö\nD\n]«°V	h5\0€¤ª§Ğ`	Ğ0dGP8]F”AUd*ò3-€!Ê%Ç˜Fé#\Z§ C½+„¡bDO1¬<8DÄà¡U‘›··÷‡—>ñQqÈ&“u¬à&5‚Y†G…€;\'kğŞuÄ“¶µXß¢Ë|ó’+\07Í¼U‡ a	Z÷ĞY„&@C½¤`³.²¥yyj¸öé[=wkØ¼ˆAC´F…\"3èd\ZÖ\nX)­\0¥HÁ+«L¡±08º	˜¬1É®_ŸÀi€%-ß#\0Šf¸‰¸egD`0X2E@r‘)p@!¦R5 Â8Fh(@kTA¼_.&µ{æ±c;—>të%ûuÎÿ¸àĞ¾ûv\"jh4ÍªÔğÚ8‚²qØSsmûI/Öb-ÖCfWs`ÕŠëı!tÖ@ëeèaz¦O°]ƒ|÷\n:Gÿşş+ï?:|ÑNåŸU‚V 4ú¹FĞTı\\ƒ¬FTr(-‡Ö¥°v„:H%ReÇ¯\n€IDOJ°ÄXËm¬—1‘(±¬ôííœt­,YÂû¢§z—ó>„Äº\"\nDô4£tÎTGp†]Å“¢0Û`õ÷óøo©8·l«Qğ“1|°!	ò_yqÁ²kÁ°XŞ„êô¡êu(¬Aw3aT¡ƒ	ìR;Ğ(V£[¾ç³ÇŸqß‰áK¶›xuMÚ@ôrAÇ€µFn5œ’ëÚHihŒ†2\nF2­ĞÑÀî6Œ‘c4pQ¢RÚ	ÂJJC°Ü¶YDŒÕØ¬ùÚÑV”<¥44ç2 ô3­vÆJv#3E°T@CbRõ\nĞ†PyF‘Àœ6¡ëÆşYúŞsn­Ü}Ì.úŸÖt6‡\ZUSBe1 ÀÉmà\nHÅáÛÀ·\\ˆ› µ+1-@k±¾Y—şf«µó¡Ì^èİç@SÛïÁô–2dPì*Ğ½Àºİÿğ¹û®¿g}ü£›\r.sÚhc\r–»+]‹h”± +GË‘åEn°Rh,e\n¹&ä \nóÀ\"å^ßÈÑÕH“\0ŒÃy`ägVsB¦€‰ãiµ%E`û¥ÜÖê_!1°é§Àí§ÑZ)(íP*X’šs)× 0;†Áj@(†¸·7WOÍÕ—íº«$í™x7 Š€qõz\0`r`ùpìHzà‡à&Ş¼8;kX_¬Z²qèğ!¨5e<´²ĞQÃ–JdÌÈúÅ½}±:çïn9zÃ‘õê‡ÆûØêı…Î˜¢6È2e-òÜ È\rƒ•Ba9¨ĞDáV1zğQègW#‡%FåÅoÕ¤ÒPèh 0@®cÏ0$ ™áÃL”ã)21LbU1í(òbñYÒRË¾42M°J€*7„,íP“QUàîhT_qï‘Í¥İ…=º²·;®8T\0;é›\r0À¸¼Ü¹\r”@+=ñ´kXÿX¯†z Ïu	¬vA÷—`ÂY/CFŒ¼—¡X W‡}êsÇ~äŞÓÕu\rô’Íz…Í,`äXíYd™0©Na±Ò5ØÓÕèYi¢©ã“¢¶È4) ĞrİG \nŒ2 h04¤,\\ÍZ‡;0i€:\0c2ac”J¹ÏUjŠA~Æ¾˜Û]Å–nµ,M\0«WhäF¼`u2ŠĞ1\"ê—MlË–eóèãÇ·wu5İ·wiÇhpmå79Ğm€r´m€İ-Óú×\0³`Z‹µ\0¬¯VoáÕP‡Aë¤ô%Ìò\ZŒŠ°6\"‹Œ<³è¬dèï®ÊCŸıâı?zïVóıtŞ-T&¬JYƒ\"·è{zl,la°»k`­FÃ\nÃ@p©¥†HD(€D+ g…ª°¯0¤mÃYÎ„ÅœnD<oû÷u˜QhB×\0CÒ4/\rˆ_k^í:C9šñ,Nÿ[-„aİ?\n€\"–ĞÏÃZü]™Vè\Z‚Œ±‹ègJ×µ?4Ü)—Vúö®Õ]½q\r°+e\0ŸÅTr7x÷=Ày‡ÀGzĞZ¬`ı£Ìêğ¦”ƒ¨Ša99d‘G¼oĞÙÓCÕÕ~îïığ½õsXiÛÉ\rL.ú”Í¥ì3™…Ê,V»İEa5&^Xˆ¢¹#U_=ä\Zi7PR\\à3\Z›»šĞ7£€a#Ì+ğŒ9-Yiá9Y\n[+0µ®‘Ë¾!dJîĞ\nú‰[¥ÿf–-fÑÏ\n\rìéhd\n¨|D®	š‘›Ü÷Ã:€Áè%/iÊÕş`µSö–»ù½««İqÀ^¹ùˆØ`¬€Í	ğ˜5àÈİ`,`X‹õÍ²¾ñ»„ÿEÀª|*hk*‹0ƒ%Œ‘…Y§k:»2ô;M}îß~öØnîTß«ŒÉ2«ÁÚ \ZYhk 3,3ØÕ±XéjTPØñ‚Zğ¨„.Ä²Ó×Ñ@A¢éTaV‰õ\r°’vœĞ«BŠcT>±¤\'ciÆ¢¶*¥D­L„c“š€½B‘\020!D \n>& @,­@š¥“ûùÀ8]Fd\n†€S¥GN\nÜ`ŒáÄaâ´–&nç€Òœ?—>}‡}¼Š¿½v`íÓ\r8t€Q	˜.X­5`\ràõu\0×Nå3àÍòŠ§Ëb=BÖ¬<l¡×Î‡b‚ŞaúK04BF\nY–#·@g9C‰ı¾O}úşNlNßÍM‡Œ7l-Ln‘åYnĞ+,öö-º¹A\"‚‹²+§IJ>E\0=ÍèiÀ€1	çY—˜C­bô­€\Z vå1TÍ5}+Œfä„två„*\0¥}*0C)àT1öâÇê\Zi–VÌÈ5ÂN*ó§&Ã&¢cD«Ú®Åßµ„¥La§·|Çz–BDå\"bd†À› šÆôãI~ÑşåÛµÉªÆ!6\rîä€n€Ø€‹% ·¬¯\'ò·(\rë\rX|“Ø’®\0­v ²e(`¬‚å6ÏÙ¹mĞéô÷Xù‡[ïÿ¾ãå‹¬U}e\rjm¦;ynå»{ƒ®1¢U9&ôÌÌ?¥1s­´´×”AÊ²Ö+5_&¨ºZ€i§Ô>X~¾g>#—Ş^*ézF€o«æéí¹¬\"Œœ”’M„­: ôbL-aXT^ÊÑ%41qŒA®Ğ·„­JB\0™BÏJÏ7òó+eâ(œJÉ§eµkü…¡¬Ü£/Ù}{ÃÊ»ˆ8q\0j\0pÌÁj¬Zğ2\'»ÃBÏZ¬G.`1áÍ3İjõèlzPÁXd™G èè­u°rä¶ãO¿÷øè¥L´O[6bSÈ\nƒ<·è»zİ#@A‘hI6íöÃgß¶¥˜””ú‘JE˜“UÀÀÛixj_ <‹-A+aGM0™Í3%@·]3\"f¶…B\"‹Õªê…j/‚¼‹@®¥ŒQ’JA˜xÆ¨èX)Ë†1l\"¬zVÁ¥¾D\"úV¬úš€Q@$ÀØøh\'ãú —eyÁÕ{J(\"¢ap¥f˜%°\0G\rğØå$ÂOíÀZ¬oÜRß°R0CC¨½tw\0£6Óy^htv[,MN.>vrüÜÀ| Ñ\Zl\rlnD`Ï,z…ÁîÜVBƒH\Z—¡P<øt4°l£$Ô¥R.Kâ»Qòs-­X¹½ôju`„t-°b	¹bt¤3T“ˆÏÓR±—Ê¼Ès.w–­öqÊàï­æÅTa5¡‰²C¹U2B‘~[“\0«K¹ôm–Î3vu4r#Y^[\r ´B77ˆD(ƒ€¦5\nÃ*¬~éîÍX¿óØöwÑ_²( ‘Y‚íöab„Qô¨£%ô5k ¼©5ê3-N›Åz\0Öœ…á\nĞ¡UĞÖ\n”Úİôa*Àrƒ,xäV£Xí OMyÎ—n_Á¤öW9e((ƒ^n`2Ñ«]ƒ¥®Y¯4Œ°RJÀF§SK°§Ph}Wz¤Í²ØWkÒ®LÀk)±š…íîHÙUû3w	xV‰n5¿©ÓõÀ³’3íBMo»ˆ,im1£–ÑË	\ZÅâ·êB8òVàcwW@$Ö\r¥…“F•\0P)¢SÛõ%Ÿ»õØuzcóQ«=­‘SƒÌU°=†!×ZëëP¸„›Ún¢h-Ö#a¥¢âš5ĞÉ±°«m]\ra\r`¡„]e½Âê=wo=c<iêµ&§5òB´*›¬ôVº¢_usåŒkq˜«Ä”t*‰Ä¦@˜	ïfšÀt-V2#°–¬Ü¶+\'ìéöu	û»„¾ÁT_ZÉ	]CSİK“<ÆÄ?Ğ±Ş1„ÀqªƒõíÄ¶RøKù(¿$Ú•\"hMğÎG,g”Ú|€Ò£öŒ•Bnú¹Æé* a©Ğ\0‰ÖU†V„õÍòğßñşgíîby@èB#³\n60LÀØô`uA_1®HLk±ëÛ[Ãâù>_ÕëAí_‚Æn˜N¶“!SŒÜf(\n…Ş¾+£“›WßsÿÎ‹F{+¥É¤Àİ}‹ıË»{½Á Ğè[BÏ\n#%^ëµZ2bEˆÉïÔKß\'H›%‰Œ±$\"¼! r^Ér\'‚‚\0’†ø°4›µ´Ã\0\"¤gZ@£Ğ<jæÀ(Ù$zğA¼[\"Â‹îÕ±”\Z­gâ<‘ìN\Z1£rÊØ*aìR¦ö¬Â S(\0áÄEXÎéÔ±UT> ×\"Æ×.À…-ú–™”n/×ÍÉıç/o‚ò5#’Œ×c°ñàu”W×àîÅ®áb=V*?´i»‰[0\0Ól–´«%ƒŞ’\n{6Ö‡×Œ›p°\"e\ròÌ\"Ïúƒ==ƒ,çº1Â:¬Ù]\0kpn!,©Œ@HµVHÚRÏHï_kæ\\-€•ŸéX g¥\\lË9®÷-¥¬+±+t”ÄÆL\Z	ê¹XÊË¶Äkwµ°\"œÍª0§iÉeíã´„T©tœ¸“\\›x|P‡ˆÕBÁ’Ø ¬¹ÉêT+Â°[î@Ê1qóûÜsúÙØšœ»»ƒn^H»bìÀt	F û¨µu¨Ç¬\'Û›¥áb}cÖ×Ï8š²­„ºhY†E¨.tC°F4æ¬ÑYëbé»N?ùşêIVŠµîe™ÆrG#jO\nÆ(Ø4†«\rÌ£tr/%ƒ¨°¬åMš$°·,h£fFé¥…¦¥8ÓpPcë[¹}L@a] T^ÊÃÊ§ç¹öÉŠà	Çğ,É-.LÅ+€Åâğ`g½›6c1Èk,)Ë¹BåÃÔ®±]Eìîh,\ZŠ…aİµQcwÏ`OßâÄva§XÂRa0š8Œš€LEÛ“\'İòé»¿ôÔg>ncƒáÊBÆ.ú®rµ‘\"¸éƒŸºeuúk±¾İJBİc/hÏQ¨†ö»¡û\r¬]‚UŒ\\Æ ³Çbåäà}÷l<ÿTÏ/I“MûJÏ¢[4Ê`©#º’u¡¥\'VI#2hÒÉ¥#OÎò¾‘İÂô´ì\"ÖIß\"¡»İµ£^V¤ù™0s£kE„Zzú–ršöF–ÇÉ5PÂ “²²††€ÕBawGa%WğÌp¾W–çÈ’0æÃ¥Ò²Œ%ø4ëĞ…~®ĞËN—Ã*@1ªŠ¶QÚË(±ÚGtŒBn€ÚE”.`¹cTh|wĞ5w.ïl|p`Ä&‚©@ìX0wÀc^xæÍZ”…‹õmXÜæ±Óa½}>Ô¾4¦[Àf\n™fäDè,eè¯Ø}ßİë×=]~×N4†’…A²­`Òa¦ĞË$©ª-ÛlÚÕËB»K¨0Ü`w&Ç²•¹b]¨<£	’måà<à‚ø ˜£&¢tÓDq»Ë(/)×:šdTˆ-¾§vu0¹LIfÖş®ÂZGš™ûVJÚB2-ÖˆÚs\ZpA˜¸€PLAŒ¤«¹€eÏPbY1rk\rn\rıLÁF80*ÄÂA@ÙäšÈ{¿Ì!\\½cTqã|Ñ86¾æ0,9Şaƒ\r,İzÖ¿øaÆcn%ÜúJÈE‹cqœu|–„I»*Ú³¥· €1[7È²™‰È—5z“Íñ[[ÕË¨ò 2£ÑÏ\rº™°¹ÆRG£›œÜ).}\nHHe“&Iõ))´a€$Ë†°7±}ƒ	=Í˜@Bû§9ng\nŠU9éç“Ñôâ½ŠS–£P¥Œª)3ƒ€K¦äõµ‚»S³Ìwš…Q ôµC!2ãm‡ÒEìÊrÒ²siÆ®]ÁÆvXš\'\rc%—äÔ‘OcÆ<C³ì&–\rÀŠÁ!¹æ-¡È€&8ÏöôúğÉ÷Şvü³».Ú?™¸èÊ:FÍ÷ª‰ÈjÎ1Æ:c×&ãK÷3pëâÏşb}Uìå›°f‚ì5k Ü\r•\r¡Ê”ĞÃØYÑA±¤1¸ûäğ±£‰;T²6²-¿»§Ñíj,u\rŠBÃ¶~¨T2…TvEÆ4Ò8¶G ›â¬š¥†:É\'%NqaY1BÆÈ“°!ÇÂ¨GpÊrGŒSz`¿íJ\0+LÍ¢\"R)r&8/¢yd rsã¿˜PùˆºEf:”M„ïLãñi¦aJqpYŠVæ\0âù‰ÒŒAÆV`aZ[%cp^_ãè¦G#Ä€Æ¥ 8bkìĞQ8wıØúáó®ŞaJ×°w¡4±ñuœŒ*TÛ#Šn“&ëww°ÁÀ£ôîÜºĞ´€4¿ËâoRÀvuÍµPG?÷e½|Ñ%j-@›.t1„‰<²\\![ÒèºrrÎÉÍÉJ¦Âh…•Á9ËıÍ2« ´Øˆ$Î8#À˜¤ò\r0P<à§¥!µÆQÆØËmU\Z.1ñF1¢†#˜#¼cËÌŠ‚„…©˜4E§ªSy˜&éø(}B1†e£ÄR¡UŠ”‰@P„Æ	{BŠ”ÉÙc¢W 4¬İ	`fŒ*`5W (¥`k‘Ø;ä]…Øq”Àõş€µBcÙ. r@ÕˆÆ•‚;“hÛ|âıwıÔ ×i6wÊà\'Â¤R•›lNÙÜÔËë~ûè‰ˆ5D¬Ÿæ…¿\0«9 úJ_ÿ³ë_°şãw|ÙşÀ¡üéá¢lyË9öéªsâ¿ŸÚ;f‚Q–s™¸µdÂÒÉû‡W–U¸h¹0X)2ìdÈs@\Z4FHÒBL:x&AXTkÜ$Ğj#d@b&{Æ‰ZÜŞ\ZÎ7l$¥ÁÅÅ@F…€9©9D/’!Ä”\"\Z%®80¢k{ÿ„õ…ÄvBÈ;Mœ²*|„ÁY\rä¬Òc·Sv(\"6@#ÆM”Ä¤e5ÌğJ£K;. .e0Fca“ì\Z²D9·a¥PÈáÑ¢°Ïà1©\"†;ñÀú‘O:çàò	Ç¡¨šŒt½3ÔØ>¥İdÓÆÍãÎ\rû^ØŠcİD`€á´`5ŸsÉg]¶<wùÍ\0XLwß}ä RÙË#ÇW3x°bpüiıÉıO\ZÜwdí‘ã±8r{™m)SûL¼`İ¹«Vû¦“g1ù«d¢Ö©Õ$JqDÛt,Ì©PgòÏ6p¯½ŞIßßöíà@CÚ]jßF3bˆ¨a(€£‡‰µ‹h\Z\'3]€€)†s*ÅMÃ\'À\nIœhjQX~62c”|®«S†²Vò»Ï™‘[FãCó\r/¦8ˆ/‚=×³(M£f\0\0 \0IDATåˆI\0–`Y36\',µ¬0¼ P¨ˆ&40!\"³„IéÑQŒaí°=ªÕ‰“şÊåûŒšŒ›ñæ5ÃÓ‡YŸ¶“Í&nrjgË7ÕF@9Œ(4£ª,ë‘Xó¿ûô×>T˜;ÚQ™i=ì€õÉO~ÒsÎ=ß¿º	áYeİt«Æ]¡/\"›}g‘Á]`¢Ûßo¶Ò[%·q¼@k­:V!)¥$&¦r2B^\'J‘ØtòV•¼K83Æ¦r°\nÂªbjT\Z/e\\b\0“àP7ì‚÷µG];/àb„âw*]DİÏt-Ÿ„yEŒ²\"Ôiç.òl®a;>lÔûó‘é6‚†aÅ1Š¥La•<FŞ£jX&C3Pè\n¦	h¼ôj³Û(%z†*ÄÒ€È–Ò$m‚ƒeF¬\"F£]C°!¢1¦òÀf1¹’QıéS¦ŞŞ.|9¬›Ñvw¶›j¼Ñp³ã•¯|§ìÔ`=2ÙÕÙ,ÊŸu¸tæ€,Îqş†\0Ö±ÛoßK]óªÆÇªšæÒÚ9j\\@`†÷Mô 5|Ô\r«\"h›8±CØ¨5kJ¤à @¬Py6Òş’§Få6lHÊÃRöyÓ®\0diç°3/ Á¢G``\0{X8¸¦AÕ4hªMÓ i\Zçàƒo&CD×r,ñ.-kĞ\r+¤ë™’]Êº‰ò[J¢|Œ;)TlğØäº·\Z0¹†©ú‘ac„v“&€#PÕ„Œ²\nSF)%+£È	y`¸ÊiÓ pÄvMXÉ\Z°3i`\\@U1\nM¨š€¨‹S™½l¹‰[§t³µİuå°r“a&Ã&NFÎ»ÊGç‚\nÜÈ,ŸxX€Ö#“]ñ µ Õ¤£šûºeax( õ°Öoşæov?uç_~èüC?ßéös…(ÛïÌŒH„H\"\r	‹¸cÀ½[@e€¨Ñ2‡oäÄ`AĞfæ·	¬XÍë€€VÛĞÜ6Û9G¹9Ën\0%ÌŠÀìĞ º\Z“²BS•¨ËU5AUÕhê\ZMİ ‡¤/	ĞkBÚL6Š!@”NaÖ²ûèBk\n]¶nzmRV˜ÛdÆbÇ¨…vB4ĞMDå#&£(S€*?…\n%mtkÄd\n\\Š0fÄáğ¦	˜Œ4‹g«I _ÖŒõ¨ÎÓıê ß>…fgkä«IíªIËq›‰ãºòÑ•ÙG01ˆãº½ë‘¢]Å9À:¨JÈŞX5Wü¸¹Ç‰sê\rİ\0ë÷~ï÷šıûw™ƒ]¬qÍµşâK.Q–´öMƒÈ$,„4@+T¬\0Ò˜8õ2Â°Ja£Š°Ã[(tT\n,„®•wÕD#{§íd¬Bä.ß!àfRğ^ûsªpÃ˜Ñ{hW£*\'Æh&”ã!ÊÉéA<zÿ2Öz™~Ä´Ï­xñâ¼\\¬¯a¼÷Ÿ?zôè_¿ıíoÿÔÍ7ßì\0Œçu£:»¤ü\'×Ãzö½ôûŸsw:ïİwà@ş„Ã‡ÃUe®–\r\Z§‚ÎQFBÃ\nFk*|âşˆ*\0\Z[A£SXd…äµ:biÈ\r¡g¥¼Êõ,!Á&••NÇ»NºÕ¼¦…d\r08ç½Cp¨K„jŒíáåhˆr¸ƒóÎ=7<ıq8·oqÛ–Ç©2J\ny>—,Òª#×ëÈpaVöµ.üÒ=p\ZÏÍ#Ìtš¾gßSñ^ÜñÂ0+¡Uû¾)…şI*jMj˜fÈıÛ_n[¥G¦duí$•´	6i¼Ø)X†ÀJ !ñ¥–î½ìàÏFĞ&TpVÁe\nN+xKŠ5!Àéá¡Ô‚e=W€m[\0Wx™÷şo_÷º×½ıæ›o\0Ø000™+ıœPÿOê kkÎ•—Zâ¼x¾6fy4\Z©Ñxt–Çîò.Ôd¨fEkTQK³¶¸w‹qlQ9`³!4¤¡­Æ ĞˆZÃ\Z£¤1™“>eç|U )›”:3˜¯m×‘!©˜æš0õ5Eïà›\Z±.1\Z01ÙÙÆÓøx¼âi—áx|i+ 2È”(Ä¤\Z’ßÊ%R«‰äµ)ùYÊW?T1åÇƒf)m0`jísÌ¤l6øTz6A°·=V$Ñ1’AÓ¹¾\\hI0\rãZ{’°R˜ÔRÔ>YdÌÊêX…İËSJéŠ\0¯	Q%p\"€jAQ˜æšĞë·T+\rà4€?QJuûÜçşòw÷wÿİûŞ÷¾´=ÌÛø«}’‡mUvòÈŠ6‡;öö#GÌÆhŒ`r8•¡b…&A‡R\Z[cc±UÉ?\"‚g……\\ËŸê~*éÚÆâŠš…mù3&\'˜E»¤Ú´Ë­~ÅQJÁàabßT(\'cT£!şÄÇãº«ÎÇ§OylÕÂ8æùk›ÊS/»Ì:l\"PÆ$°(’lö\\Kp_›l:2-.øÜr#~šÆÉÌù©‘z¾C«	À¸‘–¡0I^<H€¨k\n#Yï™‘üÂ¨éÃ´ù[…Ñ³÷ØÎC$`Túî¤r\0&0tTŒPÌRa3c*.’8øPµXíêø€·<õ©O}×G?úÑGXĞĞIûa&ÜüÆ>}İ\0kØél\0ñÑ’ -íÙ¾BŞ×›¥§‘q=2¡È2vAóñ€IÍ \"0%ƒ¨\"Ô,#«ú:5÷:™Ä\\%Æ’`yÖ†c§=z3ıŠ!â|ÖG9Ób\0W×M&hÊ	œ·×]u>>s:L·1æyj6¾İu¤™ûi^‰t‘P§‡¥—×j•¤6ôRrÃr.;u»:\n«…ÂRN)òx—Óò«–ÍûÌ@RfÖ©/0Dyü%äZÉîit†ÚEÄÑŞË4ô\\¤Mí£ltÌ½—§ñQoê%\0–í#t$¨ˆhÅÔ#èáÿµXß«iAëÆoìÎV>ÇÈ¾êfé‡óŸİ}²ëAê@*B\\tÉåØ{Á!l»ˆ‘c4P\0¬1èXË÷Ÿ.ykâ¹µ&´Ä(9–2`„U¹Ä¨Bœ-Xµ¨Ò´ƒPÛÂ:±2Õ\nò`±2Ä\0ÍŞ7ğu…ºã†§]…;vâ`5Dšdğéü•æA-}/• m†U“Ú&^FÚKî;a­«pŞÀà¼Æ¹}ƒ½=…å<!Z®fF>“Ü(†PB×ÈXúnúŞ$5hWQyqÕ·“¥Û×jaâ\"|œMñ	éºÑm}MÓ0fĞæ°YŠ3n–DÊK\ZO-´ìj‘’µX_´Şÿw¼ãg`_a}}KÂ#”¹52ÂE?\Z]Ší:`ÇE8RLĞZ#3š½wÛ¤Ab‡Ê”è2JÄùÄ¨ü<£:ëà(¥_œ+yU\" ‚`Á0Ä0ˆğÁ£ª¸ºÂÁ.À9=ƒ†ÏÜHáX4M-åßº 3÷1ZÍi>¯«õEH\Zh?SØUÈ±R(tŒèP.2šÔç˜Ú§vŸn¯CDéCÇ˜4Òº3vŒZ¬ó¥§4†ËäéÚÇ3~éÉÛÊR©xĞGÆ¤vİ8c@ƒ¦¬J…³€kşÎS¶µX‹5[Ÿ6Æ<ùÆo´_`Ñ×°¶¶ÔNÀİ‡.½lóÒ+¯ÂØÛM@5¤°°–?ï¸ë>ª‚\"•À¤ÏÅDpÏ–ÑÀ¦Oå\\:‰âY+¤;¤	ú ›‚Wê¿K£®\"4{Dxw\r®¾ô îFaw4ªéî„šiVSÅüìÏxîK¢ù:ãšlHù\'ŒIM\'à(MÌGFf‡Knz?5¨ÒÔoFD³ıa&´Í/—Ş»I	­<G[€S©mß:ƒ©iB^Õ®À0ÃJa¨R\n¦ƒ$ÒgT‹õiZïÿ™Ÿù™\'Ì•ƒó€…¯§†EÀa…¸bŸ÷ƒ?æ¯ıîïÛ4İoÕ%\'×:)t¬ÁÖéÓ|×wQˆDF¢N8‚fåII‚\0[Úİ4ä¡-ñ¦%aÊ¿jÂËÄy‹Ï`‘#<¢w¸tï¶<?ç“PN”´«yü™ÿşÜ}ZpKšö\'Ù¬o¢€héµæjí4içñ©”œßEœ™-3JšÃ¥DŒÓ×@D°š0(´$^œ1Q>“\0Ë¤Lx1»²®j_\0Ğ!BG•…A¬lg”„á}±ş‘õ…óÎ;ï™‰]µ€õUî\'`)8a~üEÏßóyÔ¿É:İK¶kO“¨P³B!³†5q¼íËw`2)¥-š ®wC©¹ORğjM˜yı;N\0©«gÃ³\\fJØUóˆ³Ë–³`¾ÒE4QzUl°»Ğˆs3Z\"HÍÄušØY,«½-Iq_)O#@z G\rc³Š8]F¬ONM\"vRYWaS˜ûó\00¥)Ò<€3‹pdÙDbP¥Ã äLM­í;ğÌS ÒJJSâ„©›P\0ĞmrRY8/ºŸ ‹²p±d9cÌcÏbVêkİ.§;]|å5ö/xæõyıàñ‰3“H¨AğQ¸cî¾ãN?vœv\rúˆdP³ËAÒ°BÒ›–”-•OI¢ìx`OšŒ3IlŠÓ™:Ne#+«Öz æÏ0´;‰2‚!ñ0µhB„U„\\Ëí>Î•L$eškG8Ï+Ë¼àÒe03Œ‘ˆÁ{x×àgnş=<áYÏ;óRï ‹ina§ïÇ¨\\iÒ¹˜[u[+ĞMÓ¥§¥[ÚµôQµóÚwåÅÈZAÒLı\\#²Ä#3Ë4™–ĞDpJR•Jj|ÈÀl\0š~¤-£jËg ‡êêÓZÿbbâPa¦t¨,Ëê¥¥¥áşıûO?ïyÏûÂë_ÿú¿_YYñ‹sÿ[rå\0ú	¬¾&;ÃÃÉ°8L¿õK?}u¿ß»~äBwâ2*4Q(ŒÁdgˆÛn»(F2Z!*+ˆ©Ä\"¸µÈÎ×¤5fÎ1¤F€ª§å{¹’r±\n8Cßñ)yt¦÷ÌÊ9f‰¨	!NÙV›QÕFÔ5óDé¹Vô€ƒğŸ?ßr3Ê±¸äÿôgá·?ö%<ñ»ŸU›o¼\ni¼ıV±YE¬O\"¶ª€aÃŸÃg²21›òTÿBïÃ™ğ‰ÏR¿Û-šd}piËP¡›iô2™–­Òs´†×2»Úò´ñ1‹ÍX©–eÅ9ÑyJ2¿¦µ¹¹ùÖo¼ñ!B0<úÑ~ô]Ãáğ—o»í¶wüÂ/üÂŸ\r‡Ãî[ßúÖ_~ùåÿöCúĞ®Å¹ÿ-¹ôYZÕƒM¸û—¬WüÊK‹s÷í~±ññQ2¡f…\0‚!B®‰ï¸ılom‰[ip2ZÍh‡Vé”(:	4İUC,ZÀhÉÈmÛéë¥4”0¾Zav›O”Å\'ı¨e1ÆiU›‹Ñ¦;è”Ç~öN!%Ä\"ŠnÏ¼îeÓãé?ğì>çÀ?ş9ĞjYV;\"lä\"ª4‘9Ä¹¶:´fíí*™(ä½Ì‰t˜i]ó/Á±;Ô>B§Z°°Jòò‰ĞÏõ”­ñ\\	Á!Ú¡[Ñ=uñL…÷V|á!”‚KKKşWõW?Ó~}İu×}ê)OyÊV¿ß^xaõÚ×¾öö/|á¿sÁ=~üøŞë¯¿ş‡N:eçÿ·ìRg•ƒ_X=l\ZÖ¿{éKŸ­ˆ^Xú k*–+\0ÈŒÆdgÇ…!\"ÙR\0øl;F®9	¾„®– ¾V(gœ<r¹Õ¤–:“IÍ_ou¬Œ¥)uò	ğ\\ÜğüÉ=í¿K Ù–=FÍ¢–§ŸnºƒÉ²¹òFÑzsönâ,foæÓšn$àL :SV?¼Ú‰A­vÕF%ÈÎz¾´€aÏ`pLcÏ C®Ê&Ìıt%F€ÛVÃBk{QS r¯Ó¨ì¯aeY6İTÍóü%_¿ß¯|å+?\n\0§NÚóÖ·¾õÊÅyÿ-»òT¯°˜Y3s‡™—wvvÖ;ry–™ô![G f…†)ùª€Â(¾ÿèQ\r‡©íD%ÀÒ¨CÄ0¹°fÖÿ7³¿ôaŞ¢¾&ˆ <ræ§£ ÄÆxn—0$ cFÓD––(—¢ñœ}rJÑôqJ&“\Z­õƒ´Ú´÷›&B‰7ô\0múŒvõ¥exğûÎ€k~—PšVşoHblÚ’Ï(Bar£¦ÏƒGpõô>A>XÍÌ\n,@•flÌ®cV‰şKúFŸùÌgo¯ò“Ÿ<ğOı|Œ‘&“‰ŞØØø¶gcßbï•¾ÂåCİ™Y0§OŸ.z=½KëŞî@ÍÑ°Ü{ìä±}VésH«sÁá\\½·\nşY»H¨£°« Ó\n¡.qÿ½÷€8Aƒ”4MŒh\"aäsº„*¸MV+&OÙVª‡ºIÃª¼°¬Nš\'A´*«dÏÔÆ4LU§­\0è@Aú]Úós,nŞÅn\0xñÆOEpæÖÊP$±9î,Œ‰˜SÃ	ø7W,C¥4bH¢üûş—\\ıd0?ñ{¡”$¬ººÂ«Şõ¸ìI×‚üÔS÷K#µ‘‡Á;ïğê›ÿ_\\|õSf¶…ôÊo|ÚyPZCiùÕFï‚ÃÿúÁ%W=?õ¬óe Å?±Şğ»Ÿ@··ğÊç\\½´uúäS”ÒLJñ¿Û;?ôò{Õà™~åC¤Õ¥Îë“/,ÆUA¿ûİïş¿â\'~â®‡ã_ùå—_>šşÃ5&€Rêéßë?ºîºë®_9xğ`yöíşç¾ç-oyË“?ÿùÏ_´³³³d­uƒÁ`¸ºº:<pàÀé¾ğ…ÿpã7Şyöı9RüÜÏıÜw|ìc{ô©S§v…ÔÊÊÊö•W^yäÆoüäu×]wüAO8c~Q)”RÜ~Fï}ï{çG~äGî\0kí/(¥˜ˆØ{oŞùÎwşnûüõ½şs³(Š7ÄµR*23B:Æ¨–––†^xá±7¾ñ~ñ‹_|ìëYK>`M&Ãçoïlş®îOvvÊÿ±¹¹ñß†›£ßó{/‡ø¶Æ5?UWÕ\rUÙ<£qş2¡=ËÉ-ù§ò7Ó\nÃ­\rŞÙ8MjúgXIKÓ¿êÛàØW`ÚÈ;íÀ	C’8ZìV8Y§Ra?å¼Ÿ}hˆ-¢šÓ³¦lNï9»m<bm›¹çÙc>³÷¯-Ui®Ïğ¦ÿçƒhÊ	ªñ×şà+ñß‹¯~òôÃÿõİ¾é7P‡øşWı;\\ö×Nï?üÕxÙ/¾Õxˆj<Äw>ÿåø¥ÜŠKğÔ™Ï³†ì_ùŸ·áGßønÔ“êÉO~ş¿ÂMÿí3xôÕOAfŞó7Gñïßû§ÓÇÙkŞŒ÷}ü(Şû±£x÷ŸİŠ^óK \"œ>z×´cà¿ÿ×£—üëÿí˜÷N¹¦Öoãrô»‹ö¤”Â‘£Çı/|ÑÇëºÎ¯¸âŠÛo¹å–w<\\`\0Ÿıìg—Úë_|ñ©Ä,~éıïÿjoå+_ùgÌ|3ßtß}÷½õU¯zÕŸìcÛ}öã½â¯xòsóœŸ¸ë®»ößtÓM¸óÎ;ßş™Ï|æİo|ãÿ¬ªªì¯şê¯ôû¿ÿû=û~7ß|ó¡Ë/¿ü5øÀø²—½ì}üãÿ?şò/ÿòÿ|ùË_şñ[n¹åÒ¿øÅÿû^ğ‚gWUõ€óëıïÿ{sY]×ù³ŸıìOŞqÇ¿Ú\0;vìmoxÃş{]×ù\r7ÜğÁy°|¨ïõŸóœ_şò—ßùc?öcQ×uŞ4Mş’—¼ä#oùÃ?üÃÿ<\Zº×_ı¿}÷»ßı¨o`1ó®ªª~Ø5î:«ÍS´±Wh­/ R»´RVkEŠ” iÖ˜àÒÑÄ…U|âş£ˆŞMãY@„­­-®ëj*×D60\'E³°½¤TòWG`˜Jfuª‘¯¥_hüÌLê¢4O»ğ@\'<’°<ÕÉx¶Køùg÷†^˜«¤°kåò’Ç=aúıÇ>ı{Ğ]^MZ•@¸-º8ü=×\0<ú±S¾\0¶èáğ÷¾dzÿ+Ÿñ}XZ]›“×1W¾:ïâğ³_0½íqOûì[Û‹UÓ’píQWM¿¿vğÒéõŞ`	Ïyé+píóÿ~ñoÑ/\n«±²º›ŞğŞy²ı¹áÎvç5¯øá§MKÂ¤×­,¯†÷üæÿõq\0xÙË~è3üã‡ç?Ö~ğƒç$Æà~ögöóíí7ÜpÃÑöúUW]5}çw^ı÷¼çï®½öÚOşñÿñ\'ÕÏÿüÏ?î·û·¿÷ÀÇ>ñ‰OüçŸüÉŸ¼ãüóÏ¯.½ôÒÉ«_ıê;¿ğ…/üÎùçŸtcc£?¿ßú­ß:øš×¼æ‡ûışø#ùÈo¾ímoûìÕW_½óŒg<cã×~í×>ı‘|ä?wŞyÇÿèşèiÏyÎs¾ÿì÷pıõ×ßß^îsŸûå³Yß={Ü›ßüæ/ÀáÃ‡ÀÒÊ{ıç<çùçŸ_½ç=ïù»öë—¾ô¥_ZYYñ×^{íÆ›Şô¦¿`fzÓ›ŞôCyøĞ\0kggçÒù	ÖfÊÚŒŒ6P)APµ[õ4ÇDÄ: `Å)§‰‚çÍõ“<ï\"œL&¼µµ•\Zœ19)ÓÖrñTRÆå	\Zs¨%Ñ®âÜÎ¡N§+iÏÑÇhÍ—U˜•ì­Ê˜w=gOg\0Ï	şS{\0Û¢¹´†9a›SªD?&\0›ŠËJâfd,}j«¡û­Éƒ?˜şŞ²·ÖÚ\\¬LSŠ‘¡9ÆGğQt«IS_æìU7n6ÓIÀæ_†Ï}äO1È\r–;…æîÖ©Ó—@ÑéF\0øÔÿúøEï|ë/]ÚFû´/µßï\00ÖÆ‡Ó<º±±aã7~ã™\0ğò—¿ü¯/¾øâÉW{ßÿñÿôßüÍß<¦ıúÎ;ïì¼ë]ïú^\0xİë^÷Á½{÷6&ò¿öµ¯ıĞ±cÇö´·:uÊşôOÿô‹cŒúõ¯ıŸ? ?îq¾ï}ïû¯D?üáşå_şåË¿âĞÙïõ_r}×w}×:\0lnn®Ş~ûíİoÃò±y\Zç(¥Î<I0ÛÒŸ©¬„6/¤£-­\"”£!v¶6çœHÄ§76¸¬*¶Š¡fD*•y\0pn‡ÑML©JÚTäY _•<ZóG[æ•Aæ\rjˆõÁ0I\0Ç)³¼Pâåêi)/Í|ãnËV¦ny>«/óisı…g–²R:ê( Š<.`Ó Uè§€úBºV¥i:C»\n->µUèe\nıttÚ‰ØQ|WS@\n1\rumu{>3Í\"yÂxU^xécñš_ùBMÿ?{o&ÉU]‰ŸûŞ‹Èµö¥wõ\"©µuKHBhÉ¶\0ÁŒŸ±„1ƒf4Ø†±‘c@Ø°Ç˜O˜İÂFcv$@BB,R£½Õ‹ª—Ú·Ü\"â-wşx/2³ª»µ·ğÏÔë/¿ÊªÊŒˆÌêwòŞsÏ=ÄN4›I\0şğò¿4—¼áì€¿ÿà_œÏ»ªî)v®››+ÖëuÙl6å7Ş8xÙe—mßºuë›z_ö²—]ÿÉO~òÖÇs¼‹/¾øàW¾ò•Ïçß¿õ­o=·ÙlVJ¥RëÒK/}èHÏ{ãß¸ëÒK/ınşı;ßùÎÓëõzÏºuë¾ímo{àHÏ»è¢‹¦Ï;ï¼;àŸøÄ³ŸNÀZşZæªT*íº‰‰‰ÂÓXÌÜğùRÈ¢th¡êp=–Y« _ÍZ\rÚb(âµÚ\"¦¦&C*fYæƒNÙ+š1Ùú\"`uÉ›ôÙ®è¦*}[Kn™’ÿ<­Hø„e¦ç¬8˜øÅğ}¯#` ò÷‹\"¼:9ŸæCûóHk)X-µ³é¶BÆaÒHƒŸ‡È²–1ƒK„ÌĞnvv¼ìø!‚K\r£‘1j©ÃbâPËüPŒ<ªë¾ ÜËëH¼4Ìgœ›š@ÚjH``tmûƒ`híQW¨(úİ7½µ´íô3§’¤UxÓë.¹(×±=U°õ¯ÿú¯goÚ´é¿÷õõıÉK^ò’ßıÂ¾pÆ9çœsßøÃ\\}õÕ7<ÖãÜu×]=ÓÓÓ‘‚Ï:ë¬…üç<ğÀ\Z\0œWJ±°Y­Vm*À\r7ÜpbàÏ<Ú¹_üâßÈùõ?úÑúöF>Òk=šëŞ{ï­@¡PHÎ>ûìù§°gOvÏ”ÊÏ˜¡Ğ$KËe]ßRWmşá7?·šu†³”ÛXÎÌLs’fì\06:“lü§»„oÖ–±¿É(+`´ĞÙü.îuÓª¶VˆĞz”\'î)ëŠøÒ`æ×«€Áè€¡‰	Ã1¡?òd}~Œ\\õİ!æi)pµg\nò!œW7@,ñpÇRÀ±m9‚kTwZŠí²vŞ\'>íJÙ´ãPİì¦vJI‡H˜9X 3Äaå/şûf’âÚ«ÿvÉ*©ôÒcÚ\0ÀhK­$şó}¬V®TÓûïùù†?ù_ÿóô§ò?åŞğ†¦§§?¢µ~ïüüü_?øàƒŸùú×¿~í™g¹øXQ¯×åe—]vö±Ç{éòßíß¿\0Ç¶oß¾U\0°iÓ¦™G{ì3ñŒÙüşO~ò“£¹‰éµÍõùÏşX\0¸ä’K¾ÿHÀÿT.µô…7UEjÄ	Ëì<C³¬mÇäŠoF·Â¾jAH \0\0 \0IDATí3F£¶H¹aRšf<=3Ã¬bfÇLN“ŠHŠĞÛ§Èo@bÆxcmÙo¦‰¤s‰í#»­‘‹*\0ëËä›¦[XÈ€ƒÊGU!\r,Æ€V„YÙ1Ë$t„œ¾Y™—œ‹—EX—Ûw\råÇ¡w²İ2R(ÃûË‡|äºù#->LkaöíFËùñw¼rÉs×l<ŞO\n8ùpÖµ_Ÿ1Vôö\ró¿ß}ÅŞËÿøû™¼ò‚—şæÅ]8_äºôÒK_sé¥};::zÈ5%IR2ÇµÉ’$)†È¬õh=ë¬³ÚÇÂÂBüxÎãœ#\0(—ËæÉ¾Ö§úœ\0°gÏÒg?ûÙÍßşö··¿ùÍoşúßÿıßßñ©ŞpÃ\r[n»íVwÏ=÷˜ö›éÙ×hÖ­Ö™³ÆÀ9ò²¦Ş¥~O¹‘Aš$í¤hnn\ZzÌÄ–Ù\n8[”1E^ÔiŸ^<™xÉÂÚ°º˜Oª	~ç]<R\n2è³V5%`]ÉGXEÑi†6l)‘OK\"LY&>„8Ï£,»L5Ÿ‹Q—Dx|(`,O£‚W£ÛÃ\'ÚMØ\0’–ßåj¯&AË	D=-Áü„Ë{sn*·¨éş£¿á/ÿúî>üÅ·vãwßu%´Î‚©hëàÀÜî·ô\n’,Ÿÿ_~}ä‚Ÿ·Ë­Şü†ß{QÒJ~áÉ÷w÷Yf~wš¦şŞ÷¾÷_Œ1‡´d¯[·n2\0Éã\"ŠûúúBš×ÿhİ»wo©]Ş¾}nI” ”€,Ëä\n*TïÒ\'ûZŸês^|ñÅÿmóæÍïx×»Şõò¹¹¹Ş™™™rvO{„õÕ¯~e‡c!¥°£«VÙ‘‘aŒ\rc``ĞöõõQµ§Å¸ ”R$#EË=£ò´J\0ĞiJÀXÃ³ssŞ d3ÇlQ”Å‚)e?^=c†b†\nP-¯J-úÈj2é€OşiO]!ƒ…øò–:¢UÊ‘ïâ=œ|²“r§5ˆ–¦{İ\\•c^BÚóòjcxÎªÇaß?Gca®½ñë¸Uó´Cex5\\ˆÀ$M9»¿áÃeGzx^T‡¨ó$%N>÷8óü@ùË0A\'hK\0)	HÙe-æ¨¼ïo¯üÔ/|Ö3†Ş»gÍkçU|ş_®¾ÿVÇîï|ç}ò\'rÿòßpÂ	ûwíÚuÌşıû×ÌÎÎFƒƒƒú±síÚµÓ³³³ƒcccÚ|}çwö‡(Î=ûÙÏ^X###³\\555U:BêY€­[·Öìk}ªÏyõÕW_yÂ	\'Ô>ó™Ï÷±}ìy_øÂ.ÔZË/}éKOËß}É\'¢µúfŒ[kÅââbt`ÿşhçƒFwŞu§úñOï·ÿè6qÛ îøéíØóğng´áü;\rßîh¤Nš£³”k‹ók,4À:ìÊˆà k`¢8ÇÀ–¿U0w¦â´gc¯÷ºñ²†ƒ-à`ìoùûs™—AÔµ¯.j¯ÉZ0şş¢öUÈvU­í·Em§»$Ââ¥òË´\rÎ-«p;æäg\0\0Æî»«#á·úÁ‡îÅğúÍè^½ÄJ™\0ÄKÚrm#Z˜\ZÇ?¿÷`)“uĞ\n¶ËİÕÙî(Q\ncl×Á_ŸÙ¼„°\0kRRL÷Ü½fíúÅ¿øĞß~“HğW¿òåóNÚºå÷ò“şG˜OÔİtÍ5×Œä?»âŠ+~ÇqjŒQõWuÒ£ñCùıg=ëY»m}´2şµ×^»1<gGooï’4kË–-`Ç«÷Ü›nºitpppvûöíõ\'ûZŸêsJ)İ©§ZûĞ‡>ôÓ?şã?ş&\0|ãß8ûàÁƒO•p×ÜØN€ï@°šòsø„ÄÎ	cĞ:­VK$IK’ğ;)«\\×”WŞÓÖh4¶Z^ı (3Œ”Á‰ kË’ à=Ê]±ÎÁ _5í§¢€ZG~å&ÀÎ:ğP\røù¼¿?@k^Ó©çÃÆ[À¾¦ÿ:™2¦Ó?¦]\'¥ÍÓÈå\rÕÑG†İœQ¹·ÿ°Ú­şşÛ@Bàöo\\Lg¡…\'\'É	·üÛ§pÆ~k	Ø¸®&é%$9/Moùò\'‘6ë@«ë‚˜ÅŒL›%hfCEµ	d–ñã[oÂ_¿ıw!„w)evHRß€ä¬#)E£Ú7to¹Ò70^öÊWíÉKóV\0[óDş#\Zc“§÷áV–e˜ŠşÃ?üÃæW¾ò•—tâµ×¼æ5×ÀG?úÑç	|>ğlİ¶mÛëòkûÛ¿ıÛ\rOgYVøÃ?üÃ#Ê&\'\'ã¯|å+ç¿ç=ï¹iùï/¿üò›‰ÈİxãÛ»1_Ÿşô§Ï¼à‚~şT¼Ö§âœGZ—_~ù=«W¯HÓ´øGôGç<í€õãïş¸™}üdÖGAsé„ƒÍJŞ’¢:CN)b€™\Z&ë†If†)1 fQ!¸ ¼m1;g´óia®D…ç³vÕ=n­½ÑRyCê€™k{À}‹Àş¦ª\\*Ğ0ÀllcM`_O¼ÏàõR5íGs±ë¼\\oá²‚#êb§x5rÌ±2¾‹ËZ½ù¼òÅ™	|ä¿ıvÿü\'HšMLîİ‰yï[pğ¡{ñ‚ßÿãCö«\0°kG‡ÓœÙ÷P;\rnÕñÃ¯_…ï_õqü™çû(9mâ†/şc\'5¹î+¨ÏÍ,°]ó…×rßOPŒŠ‘@¦\rØq>÷ÁÿM[·A†fïf³…k¾ì¥=×}ã+<??¿¿Ú?¸Ñá3¯üä§o^·~ıê)›Şò–·<3ÿşÛßşö‰wİuWÏc%‹ßñw<#ÿşæ›o^ß½¹¯ºêªõ—_~ù‹6nÜ¸äÚ>şñÿğ­o}ë¿\'IR:óÌ3ÿà²Ë.Ûvûí·÷ÍÎÎF_ûÚ×V½ğ…/|á?øÁç_uÕU_Ê+`ÕjÕ¾ï}ïûzEú›ßüæy¯ıëÏ9½à/xi«Õ*]zé¥_Şó7½ü1]tÑô›Şô¦oÖëõÊgœñê/|ák§§§£ë¯¿~èÂ/|ÑØØØÈ\'>ñ‰›ª×údÎ9??¯.»ì²m])á	yƒµ‚?ğ|Ma¿øÅ/şÊŸşéŸnŸŸŸWG°–’/¼èÂs‡úş±Pˆ·”+T*T*e”Ë%”Ê%”J%‹E¬_·[?$$ë[efa6#$ÎÙ÷ıôÜqÛÍ¼g×Ãf|z>‹z†’ÂÀh£wt}cÛ¶“Íºu›GîŸ•£SM\'¡Ğ’¨bŒ¸TDµÃF1˜Vƒ·;{±çÆ²wL˜L|ÔÄè€Ë`äÁl*ë\0£HEhTm›6`s¨ÍNa~jß~ç%øú>‡4¤tùì¿¼‡1oÂ6;“œÄ‚1>¶—<„”øøE)—´q\0_bÆƒ?ù¾yå°ëg·$0ºé8œòì‹ğ¼×ş/D…Â’h˜ñ–g\rÀYû¨È7ıß¯âØÓÎÁ;.\\ïÇ×Gˆœµ0:Åïğjl9í¼óùáÜ£ïâ7¾¯|Ã[°¦Gâ×N=”ŠÀÌltÆïù›}ï·/ù]ÅX¦)²HÀÜrÃ÷û_õŠ—ıöbm±ç³ŸûÜ\'_ÕÕFòH+Š¢Ë˜™ò]f&k­ø³?û³{×»ŞuÏ£¤(—;ç•ìÕ«^õ½«®ºê\ryã7¾ûİï>wÇ[z‰È\r\r\rÍ]pÁ÷|ä#¹íp*øo~ó›£¯}ík_>555|òÉ\'?xÎ9ç<tÒI\'Íüìg?[uİu×mŸŸŸïyË[Şòí÷¿ÿıw=Ò5}ò“Ÿ<æCúĞù=ôĞ\"âÑÑÑ™³Ï>{ç•W^yóá\\UŸìk}\"çTJ]–§‚DÄÖZñOÿôOŸzÅ+^ÑÖ¢}øÃ>şŠ+®xa£Ñ(¿ìe/»ù³Ÿıì-pyï&¢K\0Œ˜0?¾>]oñ“ —VyóæÍëŸqÆi¬TÊ/.—ËG¬uk×ãÄN	‰ÔziÎ\0³¡å¼´aï÷â{ßú:ï|pW6_OZqïp3­WVm¨tâÉúøÍ›wÎˆÍc‹6JIb\"ÈBQ©€JÙƒ—&‰5EÂtÚá®ªè‹C³´õ\\UËúßsİ5¦>bS°PN£lè¤×˜Csn\Zéƒ¸íÿ\\‚/ìum0’Ä]€×‰ %ùJ[î	0îúñíø??Ç~şô_nXRùx.­Y>ç¢(ºæNÚÖ-oLº€·¾±Ì()‚±ŒÌ;¯.Ã¿@ş[Çˆ¤\'Ê½ŒÏMıõx{…XyËj)©f¤Ú¶SqvŒRäG­ê0R!<<>ƒz+óC,ªÅ}Cƒ½?ë©ª…¨Q*DIQÉ,d\")¬ 8%|{æëh­ÙÙÙèãÿø–ë®»nËõ×_ºÖ:Ş¸qãØ«_ıêÛßşö·ß»œ·ZYO\r`-Gk±{÷î¤Ñ¨ß	?âˆË:ÛæGò2¼\"Ï/å£\\{zz „€ÑÚ†‹I…Œš$£F‹©!”\\è)ˆÔ77;”Èë}Ø:dÆB8‡˜:t·cg-Æ=¸¾T\"Ÿ:\nàÕáäÄ|ÒÂEív!ó_s-T®¢o?{åÌyr¾ŸA¾Ó÷†¾ğµ—¶–W\nN#ugÜı#Dhc\'°Ñ±rÎy§î	:¾˜Çíè»Ë™ASU*‰¢íşÂ–¶y;ç’ÿ#–B$ÀÎÂXîTZíÑiZ±Úç˜À.PÄ‚~yÆ¨êóÎ;orlllhİºuãùÈG>·gÏO¼÷½ïİ±VO‡•ù&ßoŒŞãœKˆ·tœ¹µÆbwEuÚ`ˆ€J¥‚R¹Ì™1†ÍD	H¶XF­–•\rK²Ö[Rõ’ôVÁÒ9á|ÑXcQ®­ê&x×†<Â™ÑÀ}5`*õZ­{ô\\É5®›<ç\\=Ş±›I]\'Ğ\\J–S»â×}«ÍÍáî[¿Z³åE©‰Á5W}ç¼è8ï×_†‚\0Ê\n¨(ïÔ‰˜·ÁH,õ˜?d¦a4:¨–óhİØ’ƒ–\nRÓéåo±$”cßsXT^±ßÒõÔ†şA¡åÏÉ/×Ò•@f,l^á`†5®¢µéwÎs†¢;fƒÿSGUİë}ï{ß‰^xá›ï½÷Şãöïß¿æŠ+®¸èW~åW^|å•Wnz:uI¿lëp™¸ûîûÆ˜Ä+åÊ©}}½›{z«£}}}=ÃÃCÑèèˆŒhí«FD¡‡Ø›åtÃŒŞ^ôöÀkA2Q‚Zª™!J(®–Õ|%NG2+[Æ¢ ,ÀÖ8¤Úa4{w…˜üt†óMËù~Ã-õ¬+y•{$¼Ä!sm3y˜¾ê\0dª¹ÚèèL®é’aáïŞü[¸ÿö1ºñ8üúïÿî¼ñZ¬?ñT¼î/?İNñr™‡@\0qåß#í€ˆIÈÀ ¦Ğæãs‘ƒ öÖÄËE	Ë4X\\ü´lA„Bx–y{tÚxl÷d\0>Ù%­È‡Ñæ€\0% £Ø ¿`œsJgzÀ\Z«|Pç ÚÉ³èäĞÿ‰×ç>÷¹õşğ‡/úô§?ı™/¼pêºë®ùÜç>·íúë¯?ãÆo<óíoûÂYgußqÇ7e™üÉO~²ñ‹_üâ×ÃÄÊzì€ÅÆ}×Ïîº/ìÙ&€f©TXS.—ûÊ•J±¯¯O|òIX·f­_¿†Şá3Œù¹(Š0:2Â ²Ê”BÈ&¤jY!“EM(ÎöšÙlË–æÖ±² ¶È´;‡Š>\Zb\n–½„Œ=€uK¦…onîá^àá–\'åm7èävÇ!BQ´|àiÇÕ`İÙÒù/=æ& ±0‹[¿úÏøµ×\\ŠÓŸÿÒÎ„éé´ÏÒ»æÊHµ!‹Ã¤é6`°•æÃ)EåA)ŸmæÁÃsR~t½çµŒõ€ÛÌ¬å\'ÆWÌÓF%º}Ç¸ıÁCä{«	ã,ê©n[H#z­qıÌÎOV-A])árşêw~çwö½ô¥/ıûÜJç’K.ÙwÉ%—ìÛ¹sçïyÏ{Nÿş÷¿ÒÍ7ß|Úí·ßxâ‰øÃşî\nXÀÊÇèÀa¥ù­ÕJÓV+ÍffæÔöÑäÄ”ø­ßz™X¿~åâÑ<\nŠûöç°fİ:DQÁhmR€ZÑ\"7©l!³Šç{\n‹S\r]\Zo9hïcŒjdaØ@k	%Rë™ÜÜŞÆ†&\")!œÿ@˜HcB{Î@ìµXÙR…|u)Ñy~»_0\0H× šöıg½ø<ëÅ¯‚ ?f¬exIŸa·¾Ûj&É%Ñ±Èá®\'úô:€ë:Xèë3hj¯SC õE¨$ê.¿A‡³‘eÈ.mY\0?-ˆ¶;„O#Ë1Á8ÃÚú0•<6¢ß•Œq=‚è€äHçi!ğË0B5«îuÜqÇ5?ó™ÏÜà–hyz8¬°2\0­]5Â×$€—`jµšİ¿o¿Ëçó‰\næiaD\0±ÃªÑU]5ê˜Y; …-’*Pi“U³Î¢>Ò_œë+’+€ç¯’Ì¢B1[ÔSé\\»Šå‚f+cßwøóæ•»Ì{\ZÀŞº\'Ù×—€ã«À`!×èt@Jä<Ö²ÀvôA‡8/0wâ®ëy`:Ä™4	ÇŞ:.-óô‹;‘Y˜8Ó®ú¹®¡—\Zz°êğV9Vº.Î« Ô‰üòç‡Šb;2`,	•XB\nFjì2¾pmÊj3 „pÄ’È	Aìwüòï+ë?`¥¤j\0Âm1€W@ÒjµÒıû÷[0B{-!ŞãĞtÜßß\'Nİ¾]ZÍà  ”•LS‡t&åFo_ejuOÜê‰­q€µh¤if`õÊlv¹²<ŒçÒ¡ä/Á(È¥½ƒ^º¯	<X÷“xÖ•€ã{€áBWs1u|ä—ÓŞ|8ê(°\\Š(<¯óØCÁŠÚº8¢Ìå}O;•Õ¥î]r‡®4³\rn]n\ZÜu•nÙË¶éB±rÀBˆì<yO¨bå§MgÚvš»nÌ,­µ} !…#\"DL!%\\­•õt–ÑT=\0Õ€Ùp›ƒ×M,¨ïŞ½»UoÔ9¯*u§…ò“k”tÆ™§‡˜22\"J%!³²ùL4ˆg‡ûË3#ebE6vh%‹-ƒ˜-Šğ€Õ®H…Ã“æ¼d}¾áM¸¦n\0÷/zYÂpØTõ\0¶´q™Û8ÜmN˜,Şma©ßÕòRàPßuI>åãöPW„tÃ°×CÛi–H\ZĞñì²KrQjWû\\ ßó9ŠÌXÒ?˜#`·‚ˆQ)ø‘_R®‹C$p»ò˜g|Öºª3¶(XµCÇ•µ²~€5/îš€zå·I\0Ó<ğàìâbÍäŞX\"õ#b‹Í7”¶ŸrRÑ8£»ÎeEÆYMsk2E½Ü[™\\İ£²¾ˆ\ZgŒñ›¦–8cĞ¯ŠÄ]©¡7§sƒ‘î$C\n$»ÂƒÔû\ZÀ‹¾§°*½¡ßh¡ûÍ .òıyR0ì¤ny¼³ä~~,ê\0M÷qºT!õóà!‰ÛUº~+ç°¸\rxüÆ!=…Ü@6H;r›îÇJò×Ÿ;½‚´ JbdÆÂX\ZŸ±¤K‚u¶o~~a{³Ùav’ˆù°áèÊZYOSJØÕ$€\0Æ\0ì\r·‡ì›˜˜Ø?55QÏSA¾¦·ÓB	 Z.Eç}Ö€‚™±ÌÚ9hGĞ™E6İr,.Mõ–æW—‰#vpÖ‚­®4³˜j¤Úb$fÄÄŞCÇÈ¬k;–²íp]6hƒdH˜8\\h`:cÌdŒÉ¤£E\Z.0ú£ ºH ^š&¹lc¨ÑÒ¡§‚–y¿‡ˆÇ9n«àÛjö`°gC„¥hi’\'B³w>0¶[tÊK*œÜ>¯ìš>$ºÓVö]ã$•‚@)°¡RX9Ÿ[RF\n<¥ï•B@’ˆ›­äô©©éLMMeI?óŠşhe=½€•S.Yà°æLØ`€]\0v†ÛCµZm÷ı÷=xÈ®İMĞ‘ğ©aäËKtú¶“GÏ?û¬Am´µÖ\Z°Óp¬-(›ÍDs6µŞ¾êäºŞ8ë‹k,Œ6Ö‚É&êµÔb8bô«@\Z‡Hì£¬<etÀÌqØèÆex\0‹C®®Ó©ßî\rÍˆc0fÇŒŞÈƒ.)<,¿å[pÀ]ÂÏÜ‡J,õhÏÓQÛåPjB´Õ¶éé\"ù\0Âá˜İ)(Ú-EiÇme}·o– ?Äb ¤ ‰ĞH¬c”#8òÑUfŒ¸\Z\",)¼,BJ)\"¥G± ¢5­Vëü©©Éÿoanú™Z\'=+Ûje­¥³ßò6šVWX¡CÄ5 \n  §Õjõ>ğÀıUcÍqR¨‚Ÿ³ÇDSŒ˜¶åB\\|Î³N;æîı³÷°Iœ³ÆÀj8ëtb\\:ŞD} ·4½f°¸zS=½Î¢–Ym¡H åãuÂ@I¡¿è™İfh‘ikı¦ÒÎ_ƒ$@8  Ë®]aŒà¿Š®JcË°Ÿ&Y…÷á2ahjb;U9ã°$\'ãeº†<\rkóQì…¢Y»ù¯Æ-w@ß§‰ùn5ˆ_Vˆ%y\r–ëØ=çJx\" }‚F=1h$¾‘a°¡9´RÓNÁ!\0AÂ[	Ÿ6JIPR $b%$‘ÛĞh%«2W.WîªVª»”Š\Z+[leMÀê­¼—0¿ß\0PP\n·jEƒI’­®×jÍ¾¾ş‚ ‚/!iÛ†…¡ÙŠSß´ù×ÎÚ¾áš»L˜´é´5¦ÈN[F6“ŠÆ\\&Fú{&7,$ıi\Z×,š©FEø¶ GD„A°TcBä¥Õ:XÈ”dÇ+on\ZJ-ã¹0›Hg±˜9hk‘†:¤†Úù¦j¢ ‚ğÍÊıQĞ/1CÁŸ/s^Ç”ƒ–ì\"´Û€85\"†	C1ˆsò=¤mD§õ@UP˜ Ã$qyJ¢-?á† »£ğ}„½%<jã0×Ğşu3£ô–Ç!3†R­}tå|÷£¨È[\'K) „oä#®X)\"pÙW«×Ö\'I²»\\®ÜU)WvK)Ó•­¶²&`å\\VwÄÕ„Ÿ”(¬[·nàıïÿyÛ¶r~o__?Qg0¡¢\"B$Vœc•¬<û´ãO½obaçD«Ñ,èÄZ­”J· Òƒ-Q(Oõ¯ªëUÓ-K™o×‘’`-ÁjŸã4ĞN@a0x¾W¥O¹q{Ø*àÓÆ\"y~Ë\Zg,š™ã@\0~“æduFÙ\'ğåRI@òQÅp>r¿e|Æ‘2–Pˆ¨˜©íá˜ƒÜ—Èòû¹Ï}>EG‰0ğ´+šã.€“¡à‘ãú‚ğıƒ¥ˆ…÷±eà¬Cf-ã@a0Å`Y¡Z ¶Î ™j²ÖÀ²>%‚¢+HŠ6pIáIxÏq	’¤œ*«O^\\\\Øà¬½±¿àG+[me-Àê­n¡v Y¿~}ü±}ìŒ›yùÈğğÅ‚ä€ıÎz+]ÏhyĞŠ°\"ˆ\'Áú‘cŸwÆ	Û>}Ë®	ÓXmT¹ÏH.h¤3	ê-¹°y¨gríb£o1u¥lÑsYÚú‰Í.DZ–¾µÅX@¯êÖsZÂrHß<`0„ó`EÎÂ:cÈW> İ‚’7t»e}„@FŒÅ šWÂG_±ğSœı¸0?<ÕgR­q»-F‰SêrĞé¶˜ÉõYÖùA§¹›kjv†}xWĞH\0±\"IècÑ™øœ9ÌeÆú8€6†çjA¢¯¬XIvÍ4£ÔfçÎ‚­	A)! $µÁJIoŸì‰ø¥e	!bY@š&Õ4KV­l³•u´«‹QiƒİpÃ\r£[¶lzqG¿\'„<CIQŞŸæ\\{¡ €‰ ¨ÓcèA‹\0püŒc×Ÿı¼Ùôá›ÇçîU=VÆE\r’:e‘h¨ÅÁBqjÍHßÀ|]¯]H¬;‡zf!8‚²©€XHDŒéÄa&Ø(÷( VÀLæ‹Â1fÙ‚¬·­±ÖBkilH}–FXLXâ‡•G1ÌÔ®æi¼Ûp\0gÑ©”zI£(€r\0”\\™ÙÜ\r\"ŸmHmy3µ«>Íól	ÑNÿ¼uø=ûiÏ‚€Ff‘j_95¶SPÁŒĞ2ÃmUQ	U\"î-I›˜Ô6’Lza®;‹×ı—sÚU¿oŞz?¢À[))pÆI›\0\0»Ç+íåµTßo´)uŠ§ônf~w÷÷:®óó#­Gz|ş»\'sœÇs=İ]şœÇûºVÖSX]ï9ÓÂÂÂZ§o`à¥Jªa¥TˆJl\'Ÿø$\0ÁÔVX+Áˆp`Ëè‰åè¹[×ûÀìîƒ3Í…yY()£Ì‘Î¥®ñp]ÌŸÒS™X?Òê™mÚ>Ó°T\"‡FfKX¢¢J1£\\ğ‘Mä[Œ:#Âh4‰1›XhËÈØ´Kk\r`C”ÕXRÂÜú¥-/€³€³Ëgúmš¯T—ÔQ…ÛÀ_õD„Ì.tŠÀ/QpnÈ£9jUD~ìYÔ¥r§`äçl¼ö,³ ¤y“bRºòö\0\0 \0IDATÙÚÑ¢ó¾µv>ë/+¬DN*Òz†Ì¡àEZ¯»è™øÄ×nà¾>Eú¯ç€ëü ”8{ÛfÜ½s…(ç±–\r{cOÒÆ™âá6øáÀë‘6÷#=şÑûXóx¯çH`÷D³²BÀZ\\\\™››ùmcíï!¶ÅQ$¤PA>à»ò‚ÏLHóÏÖ ~çÔÁ†›sVlé9ıâ37ÍşÓÏf¾­›5-âRÆB¦Ú!oŠÚ`Ï¬\ZêïÙP×Å¦i=íy•şˆqL/aU!Š€†edš‘hÆŒñ‘ÅÍ(KB_ô+†#‡ZêÛ~Jä°˜Ú.£@»°>BäeªQ!´uK8\' #%0¡I1¯$æÀå=ëµÌuHópœ4Ï-i\0nW+¡¥]›œÏ+Q®^Z30#–Ô—vG„¡YÖ1bA!=z\nC•ˆKE•Õ³Ô4MÎ:É°cé‰HI‰{¢ÿÏ\"}ÚÜùÀÃ\0;¤i\n¶.’ˆ¤„\0\"\0H8ƒâÑü|4\0ápÑÓ#ÕcùùÊ:Ê€ÅÌj®6÷ìL\'¯ãEq÷Ç±7tá®!ªræÎ€Â\\DÊÄ!Eb8(€E€c+í9û¢ãÍä¿ïš¿]{‘ÔÒ¦vÍ½\r,TŠ“kF{ªÍlµq™ÔìPŠÃEà¸>ã†$˜fF=aLÁ\0æ<VÃ0ŒÀ‘`ôH†C•¦µ3ÖØ6‡Å]MxL¼D½\0‚]pYè˜>Q»­†Ú<Ti˜¶­²Iù©xI©O†B…ŸÂ“k¹:3—[5SW–¯H©áöae@-ÄµQ\0/fF5©FÜ×gVPZO4kk¤pL gü˜¾8ŠğçoÇ÷~¼Ï=ó8¨€Ì§m=¦}Şïß|“+—Š(•Š(Ä1))!¥‚”ì˜˜]±;Šy¢ÿQ—?ÿÉ¤–\0ŸÌµ®DWO3`ÕjGæ^ïœy¥ò”B\\RúÍ.°Å9wEa„‹O		œzU4B+‡dŸ\ZæÖ2bÉ}§ÓaÃ.6¿w`în¡¢ŒIf¬T:ˆúŞEÌŸÔßwpËZ[0nvP/Q ‡‘°ªLX]òÖÄŒªt0ÖÂYFÄk,‰ë°à,Ê°®8Æ@M‹ì¼£æ²”PPÂ>½‘äİ€sb>—ÈğzwBËFdhÙ1ÌH‚<]Cwé©T;\nâ Œ“À¼YY?Í\'µ¼¡ÅFP.gpíÉÎìòn€ÀaIÿûr$0Úñh_1‹\nQk®‘˜Dbç±;g¼¢å’œ‹ïüè(!Ú\0Ü·kœMqğÀ>şÕçœ/¾øo_â8ŠP,8÷ü/bÄQÄR©ø±\0ĞMå^tŞ\'\n0‡{Ş\nX=€U¯Û_\"ógq¡P*Jùº{\0ğ°bé`Ø8Dğ•Â&\n„(‹Jx‡MG~´W5kÏÚĞûÜùt¡ù“ÚâXAD)ÄÅÍƒ‰X¨4QØ4Ø_Ú’ep­:“0%™ÕÖFÈd°^_•d>ŠÁàÎ8ÃŒ8‹ÄYŒ×4êM\rå,ú\" S¹Q–kO“vÛLD°àl\0ktÜ9Mqµ+~ª¡%ÈyŞ‰Ù§sŠ:³\0ÑågÅ]ŞXJí9(%CDåòÖŸzÛ™ã>\nš.c½J=o	bçN+ôl©RlÕ2›´´uìœ\"g%Ø’3œÕh¿‘’íÈ*,!\0gšF{V¡!ƒ$aÒZ£Ñh°R\nqñ¯œÿ«=Gâx%íu´¢³°úÖ}÷=xÏ†\rëXµjõ©DDKİr†¤ó•òh„¼á“/„ûŞF…ˆ C„¥BZĞêå–çlì{^º§uí½ÍÚDL½‘H›Z5÷Ö°P”Qaíè@QÕƒ“âl-£û\'Œõ\\ÓdËa¦fĞjd™ç” (òiSf|UL²EI:´2‹ffÄ mÈ`ˆU|êæÓ0Îç+äv^™Bs#Af¸ğšó+”é%u<®ÀÈœ¯ìE×Ò]âÑ¶Ëµm\\ÚÊÖu\00N‘Ï€Œ$A×–AØpÂœk+(_¥ì+JV\"W©–šd³¡µ6–‰œ`¶†Ød¾²\0 Ç¾*9ùdi†ÎR´š­Cşï¼è¿¾\0è»×}:ğóŸï¸õ”S¶ıü‘6ò‘\"”§*Å;Òq/Y¤êä\nÉş¬~ô£{şà¿¿éÆşşşmq\\Bt×€xhµÿP]n“ÔvopàÀgu6£ìù,ö``i¸¢N¹`S™õô»;ÓÖL,”²ÂÄN5Zpó…r<2lcçìªÓIôàd‹Æ5”hZFË\0Ib=IÆ„”üSHvH…‚EŸthhï9‡ˆ}Åğ‘Zn[¬¤¿¾|t=Á\rÂƒdşÆÙ¶84D!!m³íÔ’¢ÈäibÛ_\n‹ÀtœxÙğ‰Î ¤„·Ğ±ÜÖZqHÛI(øaÜ[xp ÒD×kM“\Zë,9+ÙYIÎ‚­l\râHá[·İçy|ûï{×c’°óá8î˜µíŸ_õÏÿ|¤->©øÎ8.L)Âz< t$ë‘¸­Ç>Oä8•´_°§° r„Ÿ‰ßı½7¾øŞøÚ+·oÛ6\\,”(oqÁË)ç³8¤¹+ÿ>;o]Aøãü`İ5¹Æß)$ï¯óï™ë÷šêœ,T*B©ª’ªgU	ƒ\'`d [X`|vøñV4Õ°°ğs{\nóCJ†@YHï¢ yh\ZƒÕE†IZ¨Õ0Ípcº6Ùy;şú¦É¶ƒ¨\ní(R\0±(H†v^\Z\"/×ı…«Ô®\n\"”#B=ãöñh§€í”Ğr[•	BYšÚ!µ®‹Ÿ_š6R\0ÇŞX`11H´»&‚8Õ›ú…E,+ª6ãriq!u­fªµI˜¤.ÓúBA7û`ÒÖ\r\r`dh…(F$ÑŒÆ¡‡Pg-ìÙ½Œ#”RPJ†›b!ÄL$Õİ}}ı»k[¶l™YÙj++¬\'5—ğHUBqõ¿ÿëÎ9çÌÛÙ°ş×£¡ˆrÒºüšˆpH”åÛO<HYçKß\0 UÔº<ŸÕqu°ùDegiUYm{ÎúXÈ‰ä»Z<%¨š@M·ÔâN‚:q O®^Å”YJu#zx!ÃBÊ0%‰–%\"‚ˆ$PÓ~0j“1ŠpÌh†b:XØäd»uŞ™À…I;O¨—k§EåØ7^§®SÅ#âödèü=‰£ÎÈ{B$%}ƒ²{º¶bŞµEøŸ\'Æu&şt¹<ğåN¡Î9ë¯á‚CÛ©\"«¡JìFÊ­¸\\®-fœ¤†30[Á–`\r±Ñk¬A¥\\âş~Š•\njö^‡Öb¥X\\X\\â¨“ÖYcç¹Å¸8Q(tEve®¬£™\0Ñšm|ûško9ñ„­ô÷õ÷)¥:U³¥á®\'„­…1Y–\"IÌÏÏcbr“S“(•Ê8ãŒ3Q(ƒŸÁ:?úÊˆ|n #%uÊ¹«e9Ê~p_#İ/cN2†:Ğ‹DBníí•ë×<$ĞPL§ÔH¤XÌ\0)J±D5p\0\ZAñ^äIæK„Í‚·Á#ŠÙåèª&Ú;š*\"á|D%|º%ˆÚ}Lª†Ï_e¶#Ş,E„ŞØG*hjßYFê€Høˆ«+ûóŸ ğÊvAÿ˜¢ôrˆXøi9©ñé ÁOoî)J”#72PiEåR½fĞJ,§ÖÄá,Á\Z›I¶&Rôõö¢ÇlfîÎ %ÁY‡ù¹9›c%¤¾Ì@DÎÚf~¨\\*O”Ëå¤P(è8W†Š®¬£X\0ä·Ür×i§ºoëñÇõDQ,„èŒ˜ò\0¥†1\Zssó˜˜ÇøøALLL`±VƒÖ¾<Şh´ µÆùç_Zw|4àr.«+ÒÒ!¬¥¾Hn9}X”Š2½cGİí4$Z– ö5 BßÛCÇ¬)¢A	¨İ³)µ¬E–9! µA¢Š‘@U„Z™E’9 ˆEMhËÉ#,ÑåÚéÚS­	`/ŞÌÍÃ´a0œ ë…Q6„?\"´ÅÊ§ˆ\Z~°j)è/\n–$*‘üBâ0İ´XH|d	¯§böà”G\\İ eœƒ6@’yÀM´kOÜñ-7„ş’âşrÄ#ƒ•–,ë5#Z‰q)€L°³Ì–­Ó’MÆ¬Ó¬–}ııèíEÀJ.Og€a´æ}ccvzbÂ¨(²ÅbQWª[.—3%ÕD±P˜¬T*Ír¹œ”J¥¬P(¬\0ÖÊ:º¤{Zsããc7İtËOŸùÌ3Nøµ.JE0FCÃµZ\r3Ó3Ø¿íÙ»ãh4üìø(ŠE¤”RÂï~÷»P*Â¹çÛî7”¡ZØN\r#&‚!†vU©VŸ< .,(ÛwçBë”K‰v,Ô!ÚÚÛ‡Ukˆ•å¨VØ;—Bk‹º6\0œ!d™¯Töz£M8$Î«Ş9ï /úÌŠÚêsçÎ:o\rÌA¶°ÌåâØ *`Fêü®–¶H­ç¥” Ä’ĞôÄã¼Ğ3ïï³Î@mdÃñskmóiA!‚’„·=w-ŞÍXğóòMŞåH`¸ª0T-¸ŞŞR\"‹åzM£•XNÈØ;ëœŒ!§iuZê©”ip q¤H);< €­ÁìÌ´ûíWü¶ºâŠ+š`Îœµ-fu-Õb¹¯4ßÓÓS¯V«ÍíÛ·¿ÑX5Ş÷dªs+ke=ÀÊI¯ì¾ûï½ã·Şvá©Û·­JZ	8°»wïÆÃcc4994K}7¿RP*B©¶ú=_¥R	ããã¸şúï¡§§ŠmÛ¶‡\'xK÷+8ğ@Úš\rEŒòÆŠ|–$Ûó@½uß´-Ôk,Œ%:®¯ŠÁµÒ\\•x¡TVDM§hh†s¨c¨L(I‡(&$Â!á¼5§{d„Ÿ« I†ˆÆË^‡d]§ÚF9îŒÚ’ÄHO!c¶=²u^ß¢¼a}jç¥Üö³İÖAZh[âÀqÛMµ·(1Zx¨·`{zÊ-£\nÍVj‘\nVšØy+Q›	6)Û´Y*ÆQqxh•r	gŸ¼©ıÜ¿gèô©§ƒã©©©@)Š¢–R*-‹R©T¯V«µjµZïééiôôô´ÆÇÇ?¸zõê·)¥ÜÊ6[YG°º-eììäÌ}ßùÎõwY£Ÿ›&M97;KIšBJI>’Rm•;¦æÈÄq„8Š195…k®½‘ŠpÂ‰\'úAí}ïê`d\0-hkI1WÅêTYÅÀîFrÏAM\'²Ğ˜h\nh&>¶§âF‡•9>ª…ùJ$I>4ÕÂBb}t@ƒrhPk$&AÁ9”PˆEàªxÉÜ¿Ü»ÊØ®fbòº*¢Nû‹à\"„´Ê‘è²-fï~˜9,Â=ããS‡Ìtú½%\rn·Ò ë~!èËZÚá}ßÚë”\0úK\n«zbî+é¨Tl%ˆZ‰aøÈŠXfMl-;Íl2Ø´©$\\ïğà è­VqÎÉ›èÎ÷µ+š\'lZ‡İc‚êßòÂü¼>pàÀâßüÍßLJ)uÇI±XlV*•ZOOO-«J¥’–J%\r\0‡¬•èje-ÀÊÒ´9³lìæÜzÛY«G†…ôH\0uØ’£(•Šh¶šØ7ö0¾uÍ· ­Á)§l‡$@r†*}åÍH è\0#½Z]³‘}RnÜZÁPOªÜòÎ”ãædMPfÁÍJä6Œê\r…x ·<×;TêÁÉÍ§hië\'%ÃIïŸ¥Í4¥âÔ+»Ë‘AÎÚ¹`õÂ>UÊıÜ=ÔO®¡N“7‘×Í|1u^¾@Ş¹BPÏ\0‚A=phh‡†v°Ìhj†6¬BCaV\\rÇĞÿõÜõí÷öC×îÅ[/ÚØÊÇßÙÇ3MÄ2ÒßÜB\'æ¿üöîô&°uÖdôgnzN÷ßèûÇ<hà”c;Ç÷©©ƒ1šŸqê3b\0«\0àSŸúÔ¯{İëùå/ùÚJ¥Òèéé©Ÿ}öÙ¯Ù·oß_‹EÇ±õ{ÁËÓÁÃÖá4PËûúgß²üX¥ßğÑõhÎGºÎ#=şp¯áHë±\\çátl¿,i¶z„t°=zjâÀ]ƒ#Cw\rô]XqôxO\"„@©T0!8€ë®û”TØºõÄöx04…\0\\6¨Î­ŒuĞ\0Å„UNÈŒgØ=ã¢Ùù&#Õ’k†ìæŞA3¸®˜UÊqßPe±8<Ù{gZ˜ª¥H3#\0á2k\0kmÑJ=/\\kjÄŠ+ïÖIÁ\ns\0C¿_.E—ˆÓy\"¾ DÛYA‰`·Zcš#5’<H¥Ö·Û$ĞÒ®ãì@QäÜTe‘·•ùóoìA%xëEÇ`Ó`Ğ-cIİ©BR×HŸ¿Ö}é!¾ïâcéÄ¯ïqwb-ÙêlŠ/¸æ¾™ë~}ûš¿òƒ;ŠJlê©Tª±¤Â§\\ö!ä9<‡ÚâbíóŸÿüç\\ãÕ¯~õyııı³\0Ğ××·P­V›Õjµ\0år9‹ãØ)<\\/ßcµy´şÁÇjóHç}40y\"ªö\'û¸Gë£|´×ùËÀau»Œ¶¬µ3³S“·4WœÇÑ*\"zÌãœˆ\0ckå©\r	\"LOMá†›n\08îø­B´û]ŞøÊÿ«rrÚÂ€UŸ£CãÆ&M´¯™¹æØbäšÆ™\r•²Y;¬Ì±åroµ<[,	u`NĞ¹2­Aì\0ËpaÊ4‡ægcığ†D[H\"TŠ>İ ĞGç@m\'Q/2Íë˜Š’ğ±]óEÔ–8xß{ë¼W¼5Ş­5ï?¤ ²µ!Ú\"x7Q°ŞzË\n%Å\0ht¨\'PL¨Ğl¤È2‹4\0O\0/Ú$¹0tÂ\0ĞS*­-ÆªIAŞŸ!ÂêüiŞ\0ÌZ§znvn<ãéB¡\0ÀÀÀÀ\0.”J¥¬R©¤\0P(LÇvydõX6ë‘\0î©8ÎSµÈñWRà§‡tïS?0ñ³µëÖı´··ú|!Ù©4·?™åñƒîá‡ÇÜş}û¹o N9ù¤\0‘ LOMâæ[nBš¦8eÛ©íM“×¹V+Ÿ‡àóŞ©Ó2‹»Ş!!OŠ…™uêÀŒáñ‰ºª5R¶see6ö¥£K=ÕŞJeàÀLi¨,ÅÄ|“f4¦ aï<šøåD6Q\0&ãĞÔa¨ÁX@HBQ	 es\rV.èls^|8c»È…ÿ4µ¯şiçµ`œûcÁGi… \0Uè-Jî)*î©€˜å€âB†–õ´_\0Š8€k÷êï¶†¬¶.mtk5\0”\nÑ D¹Öª\rXìÛ):£¥”¢§§*6µr¹Ü\0€¡¡¡\0èïïo\n³fÍš·æœ•‚/`=U›úh{c=\'ÒG{ì\n =5€•OCUíÌäÄÄ­«W\rŸV­VÖæÍ‡6†æxjzÚ=¼ÏØÀÎÎÎYöNnjj\Zı}}¥-Çn	.”‹øám·Â\Z‹“NÙ©\"(öi’w:@;ÊÊgúq®æfÀZeˆ‘Hğ`ÉÙ‘EgÇk-¹ĞĞÑÂ\\\n½®RÌÖ$›«åêğôLyèàL<[8ššnaÁJ$a¦‹f:ö™&K‰ÈƒZpŸ€&9p>œ!ˆGcáB‹‚:i#u2=—kØ‚Æ‹‚ß•£¨Âë¤ÎÔgE„b\"QP„Ş’âşjÑK±62JÄ³)\0øÍ-Ô&²¾¾ÇŞ.áôwöêëŸ¿1úµüç×íxø^%°éÖ{æsO>fI”|ÿî}Ø¹wİ¸®ı³}öƒˆ ¤’#ÃÃë*åÊ¤µîç!Âjä•@\0hµZï-•J—å€õHœGJkè<¾ÂÃ¥¡Ì|Dß«åœÓáîéøOÆKë±^çò÷ç—	ğèQ~\'áG{õŠãøØgû¬7®]³ú…J)’R8f¸f£é&&§ÜäÄ$ÛV³e16ğ`ùÍàÁÁÁèÌg>°aã†j!. P,\"cT*œ|Ò)ØzÒÉ(–ª¡Ü$ÆO¤ii iu\rÔ3BC44¡i€–Hœ€qÊ2m:9SƒœJTT#%cW^SAyDéŠl.”›3Ó¥‰ƒÑØq195M3“ØûÕ+ğ¯İcŒóıƒ ïĞIŒ	©Ó7˜ÿÁj¦I\nÊvòœ—wœ¡Üê¯±äÖzYCn“[ÆHòBÓJL(E’Ë±äJ9vårQ³TºåDÖÔĞ/ÙLk®~zùñtì—w¹‚ ±VÄ™kYeÌºÕG&İ áV)\"¥„-7>²R]Z+)r«k´¿ú¾QÇÌnL7sÌÆ—ÌÍÍı…RÊuGTO$²z¢QÏÑØ¤+ú°§e•^Âî(Ë„ƒ5²,›ßàÆáÁÁëµºœM§Ù™™¸ÙlEÎ9Ñõ8°4|5\0Üìì,íØq÷B±\\Z¿~İº>“ ÀZƒ;ï‡¶\Z[O8ÕŞşÎUt]RnïBmL¥¶ï[¢È¹b…íÚb¸•éù¦QÓã‰ªÏµ„ˆ(.T’A*¯+ªRµÄ…¾HG¨I\04X‰‘\Zm|Ïd’O.\rQuVÛ³‚JxÇ¹ƒC¸-!±}D–i×¶+ÎW¨z\n’+±@©q©›8•Ò4¬ĞI\n9hÃ0sâÀYyR„LÂiáŒe“ÆÈ’µd³5R ªH*nBs ÊoyE’º_¤/œsè\'Ó\0 X,šœXº€je­¬Gótï®6,ìÜ¹ëgÖòg\'¦&úšõæ(|™»@^¾”ƒUn­ğ5`&ÇwÜùóz¥TŞºfíšğafÆş}cĞZcó–ã±zÍzÏ¥˜¼K¯³™üÀ¯Î?ä÷˜ÀI±+”˜VÅÖ%œ-´29€DmRšÅæ¬QV-VgEEI@ií`Ù5SM™q°©•yi‚	ÂNTîƒrß	 ÕÚæA—¯ rP¾çå2)ÂDœàU¼ú=~t|µ(¸ZŒ¸\\ˆœŒ•eaj–L+ÉÌË£vÎö¥‡ÜÏ%±×;SINçl*Y§«Èd«Û!AŠhYT…öè°nĞ:l9…uëÖç(¼ñàøş{˜]Ÿb6¬•­´²(íøT/å²0»{÷î;Â7À¬şCç`Õ·F\0­»òÊİ{fâBœœW,l[³vÍp7¶0?‡¸Ö¬Y»•BA6ŸJÒ+Î3²ĞCçIj‘—¡œS±Ã `Ó3·ççlÖœ1i¢ÒÔ¶ÊF@©d0í3ZØLËLkÑL¥ÚB\0ËøK85t8\'©¨ëİ§@Ö{1i!È$ò´« \"‚ˆ#ÉÅ8r*V–¤´Ò6,ÙÄÀd&ô][ÌÕ;ù~IlØHb#ˆõ·vg7KF+ÖÉ›lT°ô\ZuGSKÀJt@Šóhıº\rØ·ßë³ò¯ÌŒ5«×<951\'¥¼I©èiŸê|´Ò¶•tğÿÿ°Lâ\0`1ğZqÀ‰@Oø»×¹i3|¯Ñ´W>pßM)({ÎsıŒuë×ä	 uŠ½{B–¥8fãfô–«ˆ•E-Ñ ¸PEó„µl÷&zpy !¤–à˜‰Kv\\-YSVZ›4ÕI«¥“…zªíb–ÀL&“¢’\"*e©Â¢ì¬pÖg,im„6–Œ±dó)6í6]ÀÕuÄ¤RDà‰„PJr$K%YEÒ¤s$œ°uG6Má^´™¯ŞÉ-ÃÂÎ6‚Ø\n°€ùÍcåö¯íÒ·³Î0œ)B§}2rüµ?Û«CÏ2)ÊŠÛÃ0T;ªòmE~ÜXÇ6h™/cØÈ‡~¦iræb’¾Şş\n!²ÇÊ=U +ëÿµ÷e1r]gzßYîRU]U½›‹šÍ]’#›Ší$J¶€xg#d\0AfŒÌx`=ä%y\Z Où2H2“‰<(ck/i-–(ŠâN6›½/Õ]İ]ë­»sòpÏ­:UlI¤µQôıËZ»xoUİ¯¾ÿ?ßÿı`½_-+eNMıwTY@^ß\'5€™ËÓ÷ÅúµRÀj\0è\\½r=\" âäã_úÜÉƒ»uı9i@–kk«J`ïø>ìÜõ\0\\ÇB­åƒ’”È ôN’Ş=®‹ë^?¢B¥Ø\0JEdsÙN,Š*VÂ@İ‹Ğb4fŒÆµ§ãÄv	µ]I]€0¢$JH\"¤$R(bì\"	£Q\0¡$©¶Qª¡JÓB)A”PTú\n2Œ!#	K¡ %’ÆF!U@%*,@P¢b’úÇC–TCÆE(™Cò¡Xı©_7$ª¯™¹?\rìõQìÛ»‹ó†¯}r|îŸÀüÂ¤Tnø_ğ:­æ-]`ŒİQÏà‡5‘&‹û\"\rTw›ò»ø„QËÒæ\'\0Ô5ãJî¡Q¿\nªÿĞ€•×¯ˆ¯\\¹&:~\'üê×È‰‡:¾O¿–®Y)45ÌE!â8Æş}Â.\0µhºº¥§LsšxJqšÔ†x¤À’\Z¨T Té6^ª$aRr®€ØË1#1¡4ö	%‚2ª4Ó«Ÿ\0\0IDAT8¥„QF)a$½N@©^04º–êJ)@\0JJ¢„TJ(\"c¥””*éÂéªé%ÉûÄˆ( ” JIª$ cqT\0Ùj£*Î¥î3T)8I‹ê©ñ.Šš@5ùà~\0ÀÚú\Zâ8‚Ğ¾`¦‡¿2Æ‘ @AQòÚŞ)a­Bahúƒ²£Œ]ıVÖoT÷¼ÀJYVúC,454ã9é\naº:ëÇˆş?;ë\0äÌ­9ùÓç_ˆ }æŸ=2Ñİ7\rqa½ZÁî]»àæòpód<Col»M“¡6Up(àP‹(tH2b‹)	*À$$Qˆ“îº‰PP%a+B,=ºXA(Õ„I(QD3¨ÔE™”\"}Ä«;BiÃõÄóH¢TBÙ$UJ¦nîp„ë×ÏW+BÆ.Òùı/ìqà[íúÇ³sİãÿÚc\0\0_ùì^¿<NÏ?4Ñ÷!NÍÌi€OŠ[i0ÆÀ9GGÃûöîÇüÂ\\ÿ°W\0ÀÜüLˆEq<^*•ÿı ƒºÛ–¬Çğ·ªÇP\ZÛ]±,~—¨˜Rºzè×``	ˆâmvŒé×ˆv\\,,,Š¿ÿÑ³A½ŞğøòïuÛîâ€RÈç\\äÜ„ DÁáÊXéJ†…r–0,‹&Î6S°4xÙTÂ‚—\n$\" \\7C§\n{)“¶%‰Òˆ–¨ºw)BˆIÀ„HèK’>¢ô¥eZé•ŒÈĞW”$Z\rK¥’ŒHÁ\0à™7V;DIN”¤O}nÇÿëy(üÃ³øöàù³³šU&õ©ÓfğÄ£“xãÊl—iÀÕéYÍ¨LN`f~ŒXœcµ²‚­­-ÌÌÜÂØèÊå2˜ËúR@ ßı4e_½‡YXœŠÅÒ‡Ë#ğAØUÖcxwÏûöŠ†¥Ø–ú0ËL\r•Hé\"\0\'óº\ZØéÁÇzv6›[ñŸù‘Ç‘ÿø—Oßµë\"œpåb	¶e¡åµÁø«%ÔX¢·´! Ãï(‡*´©‚Í$l(X\n`B‚†€´$OFÂ+•Ø,+İÔ+@[3Í9@¬¾¹©„¨î¬›î î Çnz›¾	\Z&@¥å§„@¤>Ô\"ÊÁøª¤g=®&`¦|)aâ:No³®›Dê Š¤?0±¶VÁÚÚ:”Rğ<Aàøñ‡°UÛDàû£ROª>0q3s·n+ÀÊãÖ\r‹ÛÅ7<ë1¼¯\"ĞqÂÀu7)âoXƒ Ó›Vµ=Zª÷yÜRŒ~òãç£µõjë›ßüúÃGİiY.\"©]qCŞ@I¯Èl‘”aé*ØT!Ç\0—*XD‚€E$  .Ã|ÕCÁê\r“H}´tÙ«èôFm¥Ø“”Ö‰9Ù^¡ß°·\0g€–yIzŠ÷ D„»\0e\0“mÊH¯Ğ¢é\n 4@)İ™Üø>b£¶µ…/ı«Äaæ¹ü	<ÏCe­\0èt|äÜãğƒäù¸í¸(e`Œ.ZœŸÓå(²Ãû*¬8/š¥ w!5\Z`\ry—êÿä°ñ6éf*:¢(\nÏ¼ü«`sc«ù{¿÷Gşõ×¾úàP¡h%\rĞ²;2‹¨	=Õ¾æ]¦Ew›(8TÁg:5-KR°˜„ç§+8¸w\'–ka¢V§ª;\05E¯º=Í½4I¥Kš&óĞÌ¬L2–\n`\re9EoXE\nP&`ÙLuÁéÌ…[xüÑI\0ÀÙ«·ºÇ{iê>sdR×«f\0\0‡\'\'»oòÅËï ÓñP¯×±¾^5Nd?¿üÄWpúÌK¨TV0::†âP…|££c	»’½…@J©¢ŒÖE,Ï*×»¬”ä½zë²Ã\']ş”ö~fiiéº¶m–…î˜e‘OpçSfÆh¸\\\0\0e\0c\0v0^,üËÿö—\'¿õo¾µ/âu¼î¬C¥İ9…™(d¢²ŒEâ§&–Wb‰ VğÂ@ åùh´=ÔkMÔj[Ø¹cşËwÏŸ_£D[\"QÙ-Ù)oÎÔ€•NgŞ†Mõ\0«Vé”gªÓÚŞ–¤|t@‘n^šQÚsAM‡FxpW®]FB€3†F£jµŠ(ŠÁXjmlßøú7ñÒË¿€Å-¸¹†Ëe”‡‡±cl\'*•UøAqƒP\n‹ó0ğÃsR©·‡ËÃ­B¡\n…ÿ,„ø‹OJùõŞÓáø¯ßûŞ÷:uêÔ€\r$}„mô”ñûÕ³ø\'x\0Ê¨i…ia_ãôŞñq÷È¡Ã”B„ˆ»í/€¢=~FôrQ	c„€‘¤èºH\nó!p˜xlÅ66Væ°Xmbr‡ƒõf\0‘Xfõt)ÓÒ“˜ÓTñ6ĞR‡§úYU7õ3›T«õS ¢FŠËRğêÊ7zuŸGH¢¨g	ëŒ£m?#ßh4\0cL­¯¯ËÍMB@èvÈÏ~şb7ñÂõz±¨TVáº®âœÃëxD)·ÛŞç_/•J±ÙK˜µédñ.q\"ã×N:•ê9ÃÔPİI¦Æ?áƒ¬y\rÖ³$\0õÕ¯íÈÄäR:‘\nBõ=†\0ˆÔLCõ´Y¢«€ï‰J]‹¡6»„ åaÈÉ•X¤€g_<?ÿw¿‹·¦×é!§éP®Û¨4mbLĞê¥‚P·—ñˆê¯S¥¬*M‰VŒô;™	d´RŒÑnj,DŒv³ƒNÇC&;P¾ï‹••Õpa~QPJÙğè°ÏåØ{1ìÄ`PÀóÚPJ¢T*#—Ë#çæd­^[nÔ›7…‚èĞ¡ïuWS„ø‹ì¼Ìb›°|çé§Ÿ~Ê`TïX÷dJ¸İ¾P\r¢qé0€]?ıéóòøãO<¥”²|¿“Ø§\rÚSJ	¥í„¥ì¥Š©sg,%„P„biy/¼ğVVV‘*¢<<Š\\¾\0J9|ò+øÆ—Nàòü:¢ØL5ûkYR3+e®&*´†EŒÛD³ª^KÏd\\éazİâŒR„A€NÇCÇk#H!@(ItUŒ+B kµºW]¯vªÕX)E…œRj‹Cöèèˆm;áœ35äœwµYé¥mÛÈçÒ÷ƒåÚVí\nç|±\\.·‹Å¢_(ÂÔe4cXYlVÿé•W^ùó“\'ONØB\"6o¢¿FÜI-‹ßCfŞSğjŸ<y’;vì cŒ‡a¨½¨ú±–êÊqú”$ŞğTEyJ!)A½ÑÄÌÍë¨m¬!Úğ½&ÖVæ!„„m»˜ºú*KßÆşÛocn¥Šº‚;–Ne·®eØ¯w§p)Cd9ø–“^e¾ç8aN)1ïïX?8ÇZ¥‚ZmQBˆ”1pÎÀ(”ÍF£İh¶\ZõZ½)¥”…B!xÇvÇv½Ş°¥T¹‘Ña§T*¾ï÷@HU*•ùV³u=Ÿ/T…‚ŸÏçCÇqâÔ+;7³¨Y\0ğ\rVÓHDæ¦Â ÃzßÂ;¿ÇÒ”KÄ\0Äwÿø»“£;Æ‰tœ¤ö©õ–VQí	O  ©ìÅUüN—.¾ƒùùÄ‘ªd\"“¢‰-Mvúüõ_ıw¼zæ—øOšÄ•©i´Ú0Ë†ëäÀ8GOYEºL/İR€\"FœR‚(†QÿªCb¬Ób¦­2!½UÆ”iµ[M4\ZuÍ¤XÚp­ ”èt:^»ÕŞò¼NÒ\Z\ZJ…¾$Š\"+Š\"\'C7Š\"×ó¼8ŠÂHI™±Rì(8Cáµš­ùN\'¸™Ïç·ŠÅ¢W(‚t:NÆ¬²Ğçl€¤ëå3\0¾ÇñkO?ıôS§Nò4X¥fiJ(p—m:ä<ğ®ÓéÃ?<ú·û7ß?räè÷)¥$‚$õSIJ˜Îî“ª?ETRõ§‹JB\n³çÎáü;ï@ÙÙYˆH$¾ñR&^ê²G{Ò¿=|ø0?yŸì1ìÛ³‰ø>‹,²Ø&Zq_\\ZZúÅ~ğƒsºÀŞ66Ó!MïªE‡ß£N\0Ğ“\'O–wîÜõ¥4\'J’ÃÓ2éĞS	ªMóz\n ú­¸pù2Î½ı6¤ˆãRˆ¤®´ÈRçd„RPÒí.Äòâ~øÌ3ø»¿{&ù?)eTşiRO¢œq0]ó±mÜ²À)eŒ2ä]Å¡\"\Z­6ZíÔ6Òô¢ËªW8ƒ…ùyÜ¸1¥bÍF³¾Qİ¨®¯W«q§¿b)í6m}¨QBb	TB\"%É°wïŞ?|äPibb™sÍ­¥ë7®_¹qıæM]wH)}`üBŞqÁ4‹û*Ô@Vd®Iûˆ}ã{h\Z\"D¸]8\n|­9+`=ùä“ó…üQBQB€\n©t\ZØ5‡HrBÒ÷ÇTßG ˆÀìÜ^}íu´ÚM\nj³ºGQH-ËêÎ†Ñö`œu\'ã$“r¥ $ª„8c\Z¼ÓÀ¤¯óô>J»Óv6·6P,phrkÕõÛÔãƒ2ˆıMKø	ˆ9¶£:9ó«åµõõJ}«¾®”jê\"fSJËø’D®Û`•õVÒ·ÕÕUÚj5™mY»ò…|ôÖÙso¯¬¬.èBi\n†æ\nOVYÜÖ^‡Û\rãz„şÖÜ)Xİ«€•ÜÙÕ«—vŒ”sG‘ù|Ø¶Mc	ËRºE’é«4‘sv‹ğ\nB	T«U¼|æW¨T*(•†P­VıWõêzEbÇ1{xd8_(rœqNe<!Â43¢Œi“.jëâ6ç,7š\\2Æ5`¥l+,Î67kX\\˜ÇP.ãÇÁv8š­úÅ[ªŸQ\r°«ô_Îmì¢ÖêJåb£ÑXC\"¾kh°2Ù•	,éûÊä4«JVY–€µZíøÌ™WÎYo{^gİ`V­biVY¤Ÿÿ`ÿp<°EØŞw[Ãº§ë—§_òoŞºïÙ»O;zT8ñÙ·g/aœƒ3F(Mæ*šh¤ˆQ·qŒ ğ³_¾„/¡T\ZBÇóƒ·Î[¼ysz€7?7åó./‹¹á‘‘á±cåR©\\*—Š9ÇÉ;ç„$¢KpÆc<*ÆÀ-Ş]™c<¨¨8Ó÷±ÄûôFõšÍ&V+«Ã{ÆÇQ­V‹Ù`ã2ºì‹qN,Îe.ç.4\ZE$Ša³ Ù1h·	,imĞÑàd¦†yô<ÍDE(ŠZÛ€ ùë˜Uƒ\ZÊA¥`Sr°º«à÷ğ›A\ZÍV=ğÃpvf†ÍÏÍ©k×®©\'N¨Ã‡=ã{”ëº	ã\"}³iôIÿÊ«¯áÕ×^‡Å9\0È©SËß¹xÀ¦>}Ïó¥çù¬RY·¸®ëGGG‡‡G‡K£#Ã¥;w”ÊåR>ŸÏ;Œ1ÆgkSËâ$«¤½…Qf%š¥´ÅÅìÌœZ^\\&c¨×¶°¸¸€& ¤DÛkëİU}—ƒK×	ep—ìßÿàf¥²6k\0–gPï·/wtjèh¶•CÏòš¡·ÚÓ¨?DYÍ*‹;-…Û=¯›œÕıX¨Õj5x„Å#õz¼ùæjvv‡ÂÁƒ‡°sç.äóypÆ»©bGxõõ×ñ~ò|ß‡]\ZR‹‹«oŸ{ûš”r@šJuôIØ=‰}ßÏ-//»ËËË9JisîÚ¶í–Ê¥¡ccCÃ#ÃùR¹˜+\r9¥rÙ)N±X´ó…#”pÅ%„PÊi·ÛX\\\\¤€Rœ3\"•ÄÂÂ<ÏÃØØX²D %Œvê®}‹Ú°”Ò‹„>ôĞQïìÙ³«øvŞ¥> úJb=q.G²mëÍ´½jÑ65‡,²x/ĞÚÄ€ßÀù^¬îú-ß“RÕ	1Ï9B<ÏÃô­›ØØÜÀøø8öîİ‡];€ëº „àÖÌŒzîùŸ’µµ*Êå¢ª×êõK.]k4\Z³\0–qÜÒ¬$ªZši¤)“+¥tÂ0tÃ0´[­–³¼´lëçY–e9®kÛãØ–åXcY¶ã:£#Ã…Ñ±±ç<çûb>ŸÛe;OUãfËËËxàİ(\nü ï³Sƒ)á\0pÎØÁƒ‡ˆİ´ÔôÍ?`¡ÛbXôxé|Y¼h½(}  º×– ¤””b³Û{u	¡ˆ¢kë´ÚMlnn`çÎ]P\nê‡?zoŸ¿€ár¾ïwægf¯¯,/OXÔ[eÀbãpôflVºi¦Õl¶Ó¿ãpp]wçW|ÂeŒ¤¦X\\ZÄÃ?Œár[r+Yùìk¢ŞÀtªK\0nÙöŞ½{mô<óÍ¹wò…0}ÌèÀ¥z\ZŸEÄpßV£Ñhnmlş|xdôÆùqBïG-t\'17Û\rÄ2ÂµkÓxí×o€3)e´´°rszjê2€e½­\0X×uŸz«hÔ`Ö@ÊdŞ7x\r<×E²ú6ìû~{sccxròÀ0ãŒuYV£†JeG…ëvA?§2,júLó4€qÎìáÑÒĞ»5ïöË$RÆí×0‹°>ì¼WSB	 ‚ súô+ÿobbßÊşıï›Øû;®›;„¤PLú±+¹¹¹¹‰8`”ªÍêÂüÌÌe¥Ô’«U\0UÍ®Zš¡ã„L•Ò\Zà4˜F™·m½oE\0;\0„³³ùG?ûÙıCÅ¡±°””X]]ÁäƒÈçBÜVxïùk	b÷&eù\\¾466F766¶«|¢_ª,²ø¨â^eXi\r%\0Ğ˜›[¼>7·X½2zåÑGùüá#‡?w`râ0%´¸!ğ}_I)IÇkW–æçÎw:ÙmÀªi°+ÙÏÙúR%:p}p3WŞ¨fY)`\0°¶¶fWÖÖföìİ=Ì9g©ûA­¶…Í*vïŞ\rßOŒñú\0Ké…½ÔnYõgvİ|y||ÜŞØØ0÷9‹,îë`÷è~ã2e¢Óéx³³óËSSÓÓqUó…<Š¥¡‚ëælÎ9±,W¯İPÓÓ3Íõµ·ê››—‘Ù—‘¬n·¢6X«1ÛL3ASÁkªxS%¯©æM‹ß€íØ¶{ìø±‰B!ïÚ¶\rË¶@ãØØ¹c¡]å;!äö\r½ë ÚÿJŠ¥·Ïÿåôôt\r½ö›Œ-e‘Ö\'˜\Zªğøa¶oİš]¾võêt£ŞZÊòQ¹\\r]×u®^›ò.œ¿ğúúÊÊ¯šUız¥÷;ÁÕ6\0Ö7’ì]ÀÌ´ËHÙ—Ól6Ù±cGvïÙ3¾“[	°rÎAÁÈÈ\nùâÈpqHÁ)y¥XÛH)!„Béy­¿~ıÍ—§¦¦êà›E`}Â€%\rPHWÆ¼N\'hÜº5³rşÜ;SíV{2Z_XXœ9wö­3RˆE®`•¶–|MÑvâ¸í„r]¿ú8íbq¨ğğ#pÇ²l×,Ëu1\\QRI‹X€ïhµ[h6›¨Õkjsk››Øªo¡İnªåÕå×^zùôÿúŸõ××ŒÔVd_ç,î÷ Ÿ‚ı3HSY‹^{Iê6à\r\rñV«ÕA¢Mj ×g×FOùQ.Õ§\"Ô€Q$ƒ4ìÚ½ë‘?ı³?şıƒ““‡(£]‡r©ŒB¡¨ªÕ*ªÕu´Ûm„a˜xÖ3Ê\\×!ã —ËÉ­­Wşé…ÿÇŸ}î\r\rÄæâAÆ°²¸¯ƒßãûgª´¯ğuz×D¯µ„·Z­T­Z[¤†a>µvº`\Zû·U]«®LOM_?~üØ¥”\'\\­¯¯ã¥—Oc£ºAlËRë —s‰ëºp]–•01ÆX\\©T^ş¹şæÅzñ’ÀY»LYJx§ˆ¦#i\nP©½Ê kÁÇÕZb.¤+ˆ–RÊj4ZêÿâŸ(—Ë%Î9BªóçßÁÜì<aŒ½p@8·À¹Ë²À-®,‹Ç•ÕÊéçòÿ÷Ïö‹HR«—™\n=‹Œa}êêZ©´\0Ø¾küãRl›û–²¬:€™™™™›7¦/ìÛ»o\\JÁ/]¼€›SSÄ¶Ä¥^a	%RJÙ	‚ -d\\[^^9ÿì~ü×®]›FÏ›ÊlHÎØU`}J€KlÆd8&°á8©¥”N7Xo¼ùæ›_ü—_øÜ­é[ã.\\BÊ0E~Ëët6¢`m=ƒõß©lmmUV—W–Ö×7+A˜62du«,~ƒÜçÇòIÌÛ,-s;ÿÃıÑWWVV÷¯®¬4ZÍÖf­ÑØô<¯Q;Ï÷ıÔ×ÊC¿\'v\nT¡Á³È\"¬,>4Ğ²0à¥î8N9‚tJé°µìv¢ÔÌê%‹°²øHŞß´×0mŒNW4Í±ZƒBÔA1ê ÕK–fñ[<{>ÒHkl¦<#4@l;;”\'‹dV/Yd+‹å}l˜´sy¯\rPe‘ğÿi·k\\XPõ¢\0\0\0\0IEND®B`‚','');
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

-- phpMyAdmin SQL Dump
-- version 3.3.7deb3build0.10.10.1
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Mar 11 Janvier 2011 à 20:40
-- Version du serveur: 5.1.49
-- Version de PHP: 5.3.3-1ubuntu9.1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Base de données: `qfacture_db_2`
--

-- --------------------------------------------------------

--
-- Structure de la table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `uID` tinyint(3) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID de l''utilisateur',
  `te_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du template utilisé',
  `name` varchar(255) DEFAULT NULL COMMENT 'Nom de l''utilisateur',
  `address` varchar(255) DEFAULT NULL COMMENT 'Adresse ligne 1',
  `complement` varchar(255) DEFAULT NULL COMMENT 'Complément d''adresse',
  `zip` varchar(5) DEFAULT NULL COMMENT 'Code postal',
  `city` varchar(255) DEFAULT NULL COMMENT 'Ville',
  `mail` varchar(255) DEFAULT NULL COMMENT 'Adresse mail',
  `phone` varchar(14) DEFAULT NULL COMMENT 'Téléphone',
  `siret` varchar(14) DEFAULT NULL COMMENT 'Siret',
  `website` varchar(255) DEFAULT NULL COMMENT 'Site web',
  `logo` blob COMMENT 'logo',
  `fac_reference_format` varchar(255) DEFAULT NULL COMMENT 'Format des références des factures',
  PRIMARY KEY (`uID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Utilisateurs de Qfacture' AUTO_INCREMENT=2 ;

--
-- Contenu de la table `user`
--

INSERT INTO `user` (`uID`, `te_ID`, `name`, `address`, `complement`, `zip`, `city`, `mail`, `phone`, `siret`, `website`, `logo`, `fac_reference_format`) VALUES
(1, 1, 'Kévin Gomez', '35 rue de vichy', '', '63360', 'Gerzat', '', '', '222 222 222 21', 'http://www.kevingomez.fr/', 0xffd8ffe000104a46494600010101004800480000ffe100164578696600004d4d002a00000008000000000000fffe00254372656174656420776974682047494d502026204279204bc3a976696e20476f6d657affdb0043000503040404030504040405050506070c08070707070f0b0b090c110f1212110f111113161c1713141a1511111821181a1d1d1f1f1f13172224221e241c1e1f1effdb0043010505050706070e08080e1e1411141e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1e1effc00011080064006403012200021101031101ffc4001d000002020301010100000000000000000000080607010405030209ffc4004110000103030204030505030a070000000001020304050611000712213141081351142223617132425281a11695d21517243336829193b1b234436272a2c2d1ffc4001a010002030101000000000000000000000000020304050106ffc400281100020201030401030500000000000000010200031104122105314151136171f014223281a1ffda000c03010002110311003f00727b9d67477d1a210edac75d0ac84eaa4decdde93b4b5ca54bafd01c9d6954be0aa743565f88f8c921683c949527046083eeabaf2d1091bdc8dd6afeca5fcdb177c4915ab16b4e9720549a4e64d3dccfbec2fb38919e24e70ae13d55c3817359d73dbf75d0daad5b9558b5280efd979856403f8543aa543f09008f4d57d5895b69e2136e2a340a5d720d49b79a0b4141c4884f0fb0ef96ac2d2413e982091df49bd93fb6fb697c54a8b45aaaa8177525ce091114ae28754693cc1520f23949c83e8411c272751d962d6bb9bb46542c7027e91fe7ac67975d515b35e23adfbb26376dddf1d36add2141bf677d788f2547a794e1e593f85473d3055abccafaf407d34e181191148c1c190a957e46637ae0edd04b65d914476a4e2c9e69525d4a5091f54f987f21a9b8391c8e90f85b82fd43c6b337bf9c0524d7bf67d9c73059e0530143e4490bfef69ef47d9cfae804181189f5eba347ae8f4d761019d1a068d1098d64e8ee75a55baa43a3d39ea8d41df2a3308e25a8214a57d025209513d000093a2136c91d33aa37c5cdd7b728dbaa959b744b54aaad419e2814f843cc9697c7369ce11f6071639ab1919033d35577885f1197c2aa6dda761dbf50a0ae620f0cb9ad704e71279712193cd81e8a58e23d404e355e58f6fc9a625da8d5d6dc8aa4a3c6fbea5175d24f52a75472a273cf181f5ebaa1afd7a68d373727c09634fa76b9b0273acfb59c7e8b12456e1aa9b5a8c7e0cc86f1664a523a28a91f7bb73ce75e57fdbb7ad6aa302b26e5555ea14e406e3bf31094cae007212a740f898e782be7cc8ce353efae8efaf1c3acea55cb03c1f1e26c9d1d64004723cc8b4aa4b17650508b8a96b8b311942b9614dac752850ea93d7b8e7aeb5b7bcbb9bb514397469cb55d3422c2db8321f512fc2594108cab99280ac7ba7963ec94f4d6fba40d6949095a148524292a041046411e8752e87aad9439c7f13e3d7da2dfa45b07d6553498f2616d9b15a6cabdaa3ce4d452acf3e24b8003fa13afd2c8f72d1d16ac4b8a7d4a1c2a7c88adc9f6890f25b6d295a42812a5103be911a8c061da33f4c69b434cad85348481eea72081cbeba8bfecba9e8918dcf5ca855d10da4b6cb7224abc9610918094827924018ec35b9a2eab58572fdc9e07de51bf48d9007a8dbde5e2976ea94e3912dc150bb272720229cd70b20ffd4eaf000f980ad42b6df7277937d2e7910a8ca8b665a911ce1a85460a43cff63e536eac105c3ea94809073e99a736a2c4a9eeedccaa05b8914cb560a93fcad516d01194e7fab6c775280e5f993cbabed655b145b42da856edbf0910a9d09be069b4f3cfaa947ef289c927b93adaa9ddc6e618945d554e01cce953e2a61c1622325d5b6cb61b4a9d794e2c80300a94ac951f524e4e8d6d0e9a352c4985743a56fc46efddcb06ef99b67b7d05c83578f813aad2923e0a1490acb2939eca1ef9cfc8770cbd66a94fa3d2e454ead3a341851d3c6f487dc086d09f524f21a4a7c475c764d7b7ce855fb42e0a7d515369ab833fd95655c2b42896d4a38c73040e5f8350ea1d92a665ee047a806700c8f5b7456297e6c871e766d4a49e39735f515baf2cf3249393d73df5bd5baf40a2464bb31c515b8785965b4f138ea8f40948e675e3326b70e03f2ddfead96d4e2bd4848ce3f4d4e761f6ceb750b286e11970d8bb2ba9cd365cb6cba8a4c52480e32df42e91cc1240008c1eb9f1fa4d19d7586db9b8136ddfe2012b1cca8665d97749b85545876eb74b71b014faa7a8f13093cf2e8e5c071f74f3f96bbf2eeea052a2a5150aec57a42103ccf2464a8fa84a738d4f2adb2fb6161c65bd712ee5beae39a4bad53597545d96e13cd7e5b7cc27279ad6ac733d49c6a3147f0fd7ddd55afe5a9748b6ac38008116121b121d611d894e485afd54e2b39ec0635af6f48d358060600ff7fb399596fb97bf2672a35757528664c78ce428a79264cc01b0a1ea94e727ea481a23d6e97325987127b125f092a525a3c4001d492390ff001d4faeed85a5d0adff0031116e0dc1ba661f2a2372e47931195e39bae70901084e7382b393803beb5b6cfc30aa98c71de57138fa1d216f53e96a2d34b5764b8f6389407a003ebaae7a353827763f3f3d4906a2dce3120a9a8429129d8ac4b61d7da195b68582a4fd46bce484388521690b4a86083cc11a612e0d98dbba851514d8b6fc7a438c0cc7990079521a57e2e3e655f45641d2caf3955a45e75cb42aa5329da4c82d096004175bcfbab29e9cc709e47bea0bba67c6bbeb3903bfb8ff0029c80fe668d26e797b67738a959b70c8a1d456029d89e4add8b291e8b460823afa91db1a6cf62bc4adb37e2d9a2dc2da6ddb8158484384fb2ca574f84b57427b21583cf00ab4a4d56ae9b7ee9a2dd70d4dbb32853da90e32143896df1025247a11feed7e8058f7dedfdea549b5abb48a9bc840756cb2a4f98da4f7524f31ff00dd7a1e9ee5e85249cfd6656a000e409331d34684f4d1abb208abf8df152afddbb6fb7a898f45a5572a0af6ae038e3505b484e7b1290b5100f750f4d443c4a5a9b7b69d9749aad9b4aa6c27e8d713306718e9f8a01654a287147de271c2ae7d78b3ab0bc79457e9f6c59f7d446ca9fb7ebeda9440fb2858e2c93e9c4d207f786b95badb772772ee05d470c3342991da6521b90a0b715e5294d4e5241092a68ac3610464a14ae7f640af77804f12cd23f69c0e62fdb93554b16f2a9cca5c765547e13296d39c8c827f4ff5d5fb676fac0a55ab48a2c4db3be9e6a9f0598a95370525386d013cbdee9eee9599b39f85705268d5592dc4a85165bf0a43c5794a149f712bcfa6475f9674d149bfb68a7bad1834aa14642996d0af3554f0a648393c27ce1c5e9cfaf7d57d0e896aab61f663dda96dfb967695bf6c32e38fff003497f36b5801c7053520a80e809e2e6064ebe695e242db93725328952b4aeaa3aea32511597a646425016a3c201f7b38c91d35d17f72b64528f7a8b413f4552c9fd1fd2e9e22ab169dd3765198b06032c87df651ec509d690b79fe25e5690d2948413c4da42bafbb9c606a7f854f1887ea1c7398d56f1ee850f6c69d4f955787509cba83ea6233309b4a94a29009ea401d47a939e9a81a3c41c595cd8db4be5cfa4249ff00db4b86e15af5bb4ead6eceacda954b5995cd07da26d57db10b50e124f21ee91cce3b8fa6af8b3ef7dab8d222fb553a865b6f854b538b80a5abdc00a32b786467ef1e6719e475d4a131ee71f55606f53b0f6f92c0255b597fa53dcaa9e31feed2fdb9575b351dda7ee65dbd5aa3c4aa466a3a933e3f96af3538055d7a600f9f5d33137717654b641a35bea04630174b39ff0007f4ba7897b8ec9aa269a2cd8d0e0c6614d8723c75b3f1540b878f85a5a92300e324e4e7e434ad4aba94c77835ee70499cfb42d0a15ebbd74cb66b626062a909d495c45f0ad875085292b390463ddc608c73d4cae9b4e9bb4d7bed45d160d57db04d9622bafb5ee89c90f81c440241e26dce038e47841c73d1b4db5d57ba6ce55d8cbac45aa5764284799e7a926043405a54901042965e57c250e810547ae3536b95b5dcbe267696d47a0478828f11351930a3ab8d98ca402b0849039a4790800fa11ae500a054cf69db002a588ef1c1034681f5d1ab729c87ef1592c6e1edad66d090f25833d90197949e20dba9505b6a23d389233f2ce961a4db3e2aecea631438744a4d6a14148663bbe7b2b516c7248c95a57803a64671a7375f2a1cf96b8543779d5665ed3f3ebc2cdb122f3ddeae5db70d3e04862238ff00b6477509524497b8b002159040f7fd7181a6c1367d9d8fec9d03f76b3fc3aa06c074ec26eedc569dee8f65a6dc32848a5d6387e0b80295c2147ee8c2f07f091cf91074c834fa56da5685254950e24a81c820f420f718efaa77921a69697694face78b3ecdc7f64e81fbb59fe1d7a45b6ad7852912a15b9478b21b3943acc1690b49f910907f5d6ff009baf97de0d35e63a4368fc4be43fc750e49967004f2ab42a7d5237b354a0c498c710579721a4b88e21d0e1431ae2aed0b43b5ad41fddcd7f0ebcab17e59b4a25352bae891543aa1735be2cff00db9cfe9ae7c6dc1a0d45c0d511aab5654a380b874d78b5fe6ad2947fe5ae8dd1095266f3968da39e56b50bf7733fc3aae37bf6b6d8add04d4534f874f6a910e64a5370e3a5953eb0c92d8529207ba0a73f3e9dcead96de5b8c21c7195b0b50c96d6524a7e478491faeaaaf109b834eb76d7956ec7266dc1598ea89120b0389c1e6828e320648185721d49e9a74ddb86225a1021ccab761ab1bf35ab099a7edddb94c9d48a63ab87ed0f2909505e7cc29256e273fd60ed8e7abdbc35ed0de745beeafb99b9d2e33d714e60c68f1d9712b0c2091c4494fba0e12948093c8679f3d48fc1fedd55b6db69d14eaf7c3a9d4e5aea2fc7e5fd1b8908425b2475504b609f9923b6ae6031ebaba14039c4cb2ec46099919c68d031e9a34d1663bf5d07ae8ee796b3dfa68848b6e5d876e6e15aefdbf73404c98ae654dad3c9d6178e4e36afbaa1faf4208e5a5544ebe7c3857d9b7af0122bd60bebe0a7555b49518d9fba79f2239e5b27d4a0f6d3a7db5ccb928348b8e8b268d5c80c4fa7ca4703f1de4052163afe441e608e60f4c6959430c18c8e50e44ab1b9349ba682c4d835579da73e9f31a7e0cd5b3c69c7e24107f2e583a865d9b556fce84b7205363d427f185015c9d324b2a1dc101dc8faf3fa6a177fedbdf1b0eba9572c5724dc1614a43867535c5153b042810563d401ff30761ef8e59d587b417535756db512afe7b6e4954543324058243c8012ac8ec4919fcc7aeaa356d5f69a096ada307bcd4dbeb115439dedb50a55a10421be16a351e98120a8e3df5baef12c918e4060732493a9e29d19c678880397a67a7fa6bc56f27bad233ea796a809574ee06e5ee2dc962ed9a1b69b121b6e4d614e611123a1010a208e9c4bf3398c923000ea74aa8ce6333ad42493763766442aba2c7dbe84aaeddf2d6594a184f9888aaef9c722b1cce3a0c6547b6ac1f0f3b0cdd9d2cde97aca15ebde5fc472438af3110c91cd2d93d55cf057f927039994ec56cc5afb55492980933eb5213fd36aafa479ae9ee94fe0467ee8ebdc93ab3c0c0d5c44083899f65a6c3cc0003d06b3e9cf47af2d03b72d3c8e03eba340d1a210efa3468d10868c68d1a2135e7c58f3613f0e5b0dbf1df6d4dbadad394ad0a185248ee08e5a57af7f0abb62cd4de934f917053d2b3c69658988286f3d93c6da958fa93a34688483d1bc39d933ebfec126ad722990bc7fc5359c7f95a68f6736aecfdaea3c8836ac47d0a98a4ae54890ef98f3c4642413800019380001cce8d1a2127a07fa6b3db468d1087ae81db468d1080d1a346884fffd9, '');


-- --------------------------------------------------------

--
-- Structure de la table `article`
--

CREATE TABLE IF NOT EXISTS `article` (
  `aID` smallint(5) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID de l''article',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce produit',
  `name` varchar(255) NOT NULL COMMENT 'Désignation de l''article',
  `price` decimal(10,2) NOT NULL COMMENT 'Prix unitaire',
  `comment` text NOT NULL COMMENT 'Brève description',
  PRIMARY KEY (`aID`),
  KEY `a_owner` (`u_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Table des articles' AUTO_INCREMENT=4 ;

--
-- Contenu de la table `article`
--

INSERT INTO `article` (`aID`, `u_ID`, `name`, `price`, `comment`) VALUES
(1, 1, 'Truc cher !', '2005.07', 'Juste pour tester'),
(2, 1, 'Prod de test', '50.00', 'toto'),
(3, 1, 'Truc', '5.00', 'bla bla');

-- --------------------------------------------------------

--
-- Structure de la table `client`
--

CREATE TABLE IF NOT EXISTS `client` (
  `cID` smallint(5) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID du client',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil auquel est rattaché ce client',
  `name` varchar(255) NOT NULL COMMENT 'Nom du client',
  `address` varchar(255) DEFAULT NULL COMMENT 'Adresse',
  `complement` varchar(255) DEFAULT NULL COMMENT 'Complément d''adresse',
  `zip` varchar(5) DEFAULT NULL COMMENT 'Code postal',
  `city` varchar(255) NOT NULL COMMENT 'Ville',
  `phone` varchar(14) DEFAULT NULL COMMENT 'Téléphone',
  `mail` varchar(255) DEFAULT NULL COMMENT 'Adresse mail',
  PRIMARY KEY (`cID`),
  KEY `c_owner` (`u_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Table des clients' AUTO_INCREMENT=3 ;

--
-- Contenu de la table `client`
--

INSERT INTO `client` (`cID`, `u_ID`, `name`, `address`, `complement`, `zip`, `city`, `phone`, `mail`) VALUES
(1, 1, 'Laurence Gomez', '35 rue de vichy', '', '63360', 'Gerzat', '', ''),
(2, 1, 'Kévin Gomez', '35 rue de vichy', 'toto', '63360', 'Gerzat', '0698568827', 'contact@kevingomez.fr');

-- --------------------------------------------------------

--
-- Structure de la table `facture`
--

CREATE TABLE IF NOT EXISTS `facture` (
  `fID` mediumint(8) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID de la facture',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil ayant créé cette facture',
  `c_ID` smallint(5) unsigned NOT NULL COMMENT 'ID du client',
  `tr_ID` tinyint(3) unsigned NOT NULL COMMENT 'Mode de règlement',
  `td_ID` tinyint(3) unsigned NOT NULL COMMENT 'Type de document',
  `amount` decimal(10,2) DEFAULT NULL COMMENT 'Montant total de la facture',
  `comment` text COMMENT 'Commentaire',
  `Date` char(10) DEFAULT NULL COMMENT 'Date de la facture',
  PRIMARY KEY (`fID`),
  KEY `idClient` (`c_ID`),
  KEY `f_owner` (`u_ID`),
  KEY `td_ID` (`td_ID`),
  KEY `tr_ID` (`tr_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Table des factures' AUTO_INCREMENT=2 ;

--
-- Contenu de la table `facture`
--

INSERT INTO `facture` (`fID`, `u_ID`, `c_ID`, `tr_ID`, `td_ID`, `amount`, `comment`, `Date`) VALUES
(1, 1, 1, 1, 1, '4010.14', 'tata description', '2010-10-19');

-- --------------------------------------------------------

--
-- Structure de la table `factures_lignes`
--

CREATE TABLE IF NOT EXISTS `factures_lignes` (
  `lID` mediumint(8) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID lien',
  `f_ID` mediumint(8) unsigned NOT NULL COMMENT 'ID facture',
  `name` varchar(255) NOT NULL COMMENT 'Désignation de l''article',
  `quantity` smallint(5) unsigned DEFAULT NULL COMMENT 'Quantité',
  `price` decimal(10,2) DEFAULT NULL COMMENT 'Prix unitaire',
  `off` decimal(5,2) unsigned DEFAULT NULL COMMENT 'Remise (%)',
  PRIMARY KEY (`lID`),
  KEY `idFacture` (`f_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Lignes des factures' AUTO_INCREMENT=3 ;

--
-- Contenu de la table `factures_lignes`
--

INSERT INTO `factures_lignes` (`lID`, `f_ID`, `name`, `quantity`, `price`, `off`) VALUES
(1, 1, 'Truc cher !', 1, '2000.50', '0.00'),
(2, 1, 'Prod de test (!)', 2, '50.00', '10.00');

-- --------------------------------------------------------

--
-- Structure de la table `template`
--

CREATE TABLE IF NOT EXISTS `template` (
  `teID` smallint(5) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID du template',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce template',
  `type` varchar(10) NOT NULL COMMENT 'Type de template',
  `name` varchar(255) NOT NULL COMMENT 'Nom du template',
  `content` text NOT NULL COMMENT 'Contenu du template',
  PRIMARY KEY (`teID`),
  KEY `te_owner` (`u_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Templates de facture' AUTO_INCREMENT=2 ;

--
-- Contenu de la table `template`
--

INSERT INTO `template` (`teID`, `u_ID`, `type`, `name`, `content`) VALUES
(1, 1, 'html', 'Thème par défaut', '<html>\r\n<head>\r\n	<style type="text/css">\r\n	/* GENERAL --------------------------------------------------------*/\r\n\r\n	* {\r\n		margin: 0;\r\n		padding: 0;\r\n	}\r\n\r\n	body {\r\n		background: #fff;\r\n		color: #393939;\r\n		font-family: Arial;\r\n	}\r\n\r\n	img {\r\n		border: 0;\r\n	}\r\n\r\n	p {\r\n		margin: 0px;\r\n		padding: 0px;\r\n	}\r\n\r\n	/** logo **/\r\n\r\n	#page-top-outer {\r\n		background: url(images/top_bg.jpg) top center repeat-x;\r\n		border-bottom: 1px solid #7e7e7e;\r\n		height: 92px;\r\n	}\r\n\r\n	#logo {\r\n		float: left;\r\n		margin: 45px 0 0 45px;\r\n	}\r\n\r\n	#logo h1 {\r\n		color: white;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 30px;\r\n	}\r\n\r\n	/** Contenu **/\r\n\r\n	#content h1 {\r\n		margin-bottom: 10px;\r\n	}\r\n\r\n	#content {\r\n		color: #333;\r\n		font-family: Arial, Helvetica, sans-serif;\r\n		font-size: 12px;\r\n		line-height: 18px;\r\n		padding-top: 2em;\r\n		padding-left: 4em;\r\n		padding-right: 4em;\r\n	}\r\n\r\n	/** Tableaux **/\r\n\r\n	table {\r\n		border-collapse: collapse;\r\n		margin: 10px 0;\r\n	}\r\n\r\n	th {\r\n		height: 50px;\r\n		padding-left: 10px;\r\n		padding-right: 45px;\r\n	}\r\n\r\n	td {\r\n		border: 1px solid #D2D2D2;\r\n		padding: 10px;\r\n	}\r\n\r\n	/* Détails d''une facture */\r\n\r\n	.align_left {\r\n		text-align: left;\r\n	}\r\n\r\n	#invoice_mentions {\r\n		margin-top: 20px;\r\n	}\r\n\r\n	#invoice_right_part {\r\n		text-align: left;\r\n		float: right;\r\n		margin-top: -120px;\r\n	}\r\n\r\n	#invoice_customer_name  {\r\n		font-weight: bold;\r\n	}\r\n\r\n	#invoice_products {\r\n		text-align: right;\r\n		width: 100%;\r\n		margin-top: 30px;\r\n	}\r\n\r\n	#invoice_products tfoot td {\r\n		border: none;\r\n	}\r\n	\r\n	#invoice_compagny_infos {\r\n		text-align: center;\r\n	}\r\n	</style>\r\n</head>\r\n<body>\r\n<div id="content">\r\n	<div id="invoice_compagny_logo"><img src="{% logo_url %}" alt="" /></div>\r\n\r\n	<p id="invoice_compagny_adress">\r\n		{% ae_name %}<br />\r\n		{% ae_address %}<br />\r\n		{% ae_zip %} {% ae_city %}\r\n	</p>\r\n	\r\n\r\n	<p id="invoice_mentions">\r\n		N° SIREN : {% siren %}<br />\r\n		Dispensé d’immatriculation au registre<br />\r\n		du commerce et des sociétés (RCS) et<br />\r\n		au répertoire des métiers (RM)\r\n	</p>\r\n	\r\n	<div id="invoice_right_part">\r\n		<p id="invoice_customer">\r\n			<span id="invoice_customer_name">{% customer_name %}</span><br />\r\n			{% customer_address %} {% customer_address2 %}<br />\r\n			{% customer_zip %} {% customer_city %}\r\n		</p>\r\n\r\n		<p id="invoice_date">\r\n			{% invoice_date %}\r\n		</p>\r\n	</div>\r\n\r\n	<span id="invoice_number">Facture n°{% ref %}</span>\r\n	\r\n	<p id="invoice_desc">\r\n		{% invoice_comment %}\r\n	</p>\r\n	\r\n	<table id="invoice_products">\r\n		<thead>\r\n			<tr>\r\n				<th class="align_left">Désignation</th>\r\n				<th>Prix unitaire</th>\r\n				<th>Quantité</th>\r\n				<th>Montant (EUR)</th>\r\n			</tr>\r\n		</thead>\r\n\r\n		<tbody>\r\n			{% product_line %}\r\n			<tr>\r\n				<td class="align_left">{% designation %}</td>\r\n				<td>{% prix_unitaire %}</td>\r\n				<td>{% quantite %}</td>\r\n				<td>{% montant %}</td>\r\n			</tr>\r\n			{% product_line %}\r\n		</tbody>\r\n\r\n		<tfoot>\r\n			<tr>\r\n				<td class="align_left" colspan="2">Total HT</td>\r\n				<td colspan="2">{% invoice_amount %}</td>\r\n			</tr>\r\n			<tr>\r\n				<td class="align_left" colspan="3">TVA non applicable, art. 293 B du CGI</td>\r\n			</tr>\r\n		</tfoot>\r\n	</table>\r\n\r\n	<p>\r\n		À régler par chèque ou par virement bancaire :\r\n	</p>\r\n\r\n	<table>\r\n		<tbody>\r\n			<tr>\r\n				<td>Code banque</td>\r\n				<td>Code guichet</td>\r\n				<td>N° de compte</td>\r\n				<td>Clé RIB</td>\r\n			</tr>\r\n			<tr>\r\n				<td>12222</td>\r\n				<td>22222</td>\r\n				<td>22222222222</td>\r\n				<td>22</td>\r\n			</tr>\r\n			<tr>\r\n				<td>IBAN N°</td>\r\n				<td colspan="3">FR22 2222 2222 2222 2222 2222 222</td>\r\n			</tr>\r\n			<tr>\r\n				<td>Code BIC</td>\r\n				<td colspan="3">Code bic</td>\r\n			</tr>\r\n		</tbody>\r\n	</table>\r\n\r\n	<p id="invoice_compagny_infos">\r\n		{% ae_name %} – {% ae_address %} – {% ae_zip %} {% ae_city %}<br />\r\n		Telephone : {% ae_tel %} – Site Internet : {% ae_web %} – E-mail : {% ae_mail %}<br />\r\n		N° SIREN : {% siren %} – Code APE 6201Z\r\n	</p>\r\n</div>\r\n</body>\r\n</html>');

-- --------------------------------------------------------

--
-- Structure de la table `types_documents`
--

CREATE TABLE IF NOT EXISTS `types_documents` (
  `tdID` tinyint(3) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID du type de règlement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de règlement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de règlement',
  PRIMARY KEY (`tdID`),
  KEY `td_owner` (`u_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Contenu de la table `types_documents`
--

INSERT INTO `types_documents` (`tdID`, `u_ID`, `name`) VALUES
(1, 1, 'Facture'),
(2, 1, 'Devis');

-- --------------------------------------------------------

--
-- Structure de la table `types_reglements`
--

CREATE TABLE IF NOT EXISTS `types_reglements` (
  `trID` tinyint(3) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID du type de règlement',
  `u_ID` tinyint(3) unsigned NOT NULL COMMENT 'ID du profil utilisant ce mode de règlement',
  `name` varchar(255) NOT NULL COMMENT 'Nom du mode de règlement',
  PRIMARY KEY (`trID`),
  KEY `tr_owner` (`u_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Contenu de la table `types_reglements`
--

INSERT INTO `types_reglements` (`trID`, `u_ID`, `name`) VALUES
(1, 1, 'Espèces'),
(2, 1, 'Chèque'),
(3, 1, 'Virement');


--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `article`
--
ALTER TABLE `article`
  ADD CONSTRAINT `article_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE;

--
-- Contraintes pour la table `client`
--
ALTER TABLE `client`
  ADD CONSTRAINT `client_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE;

--
-- Contraintes pour la table `facture`
--
ALTER TABLE `facture`
  ADD CONSTRAINT `facture_ibfk_4` FOREIGN KEY (`tr_ID`) REFERENCES `types_reglements` (`trID`),
  ADD CONSTRAINT `facture_ibfk_1` FOREIGN KEY (`c_ID`) REFERENCES `client` (`cID`) ON DELETE CASCADE,
  ADD CONSTRAINT `facture_ibfk_2` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE,
  ADD CONSTRAINT `facture_ibfk_3` FOREIGN KEY (`td_ID`) REFERENCES `types_documents` (`tdID`);

--
-- Contraintes pour la table `factures_lignes`
--
ALTER TABLE `factures_lignes`
  ADD CONSTRAINT `factures_lignes_ibfk_1` FOREIGN KEY (`f_ID`) REFERENCES `facture` (`fID`) ON DELETE CASCADE;

--
-- Contraintes pour la table `template`
--
ALTER TABLE `template`
  ADD CONSTRAINT `template_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE;

--
-- Contraintes pour la table `types_reglements`
--
ALTER TABLE `types_reglements`
  ADD CONSTRAINT `types_reglements_ibfk_1` FOREIGN KEY (`u_ID`) REFERENCES `user` (`uID`) ON DELETE CASCADE;

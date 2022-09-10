CREATE DATABASE  IF NOT EXISTS `db_sluiceGate` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `db_sluiceGate`;
-- MySQL dump 10.13  Distrib 5.7.39, for Linux (x86_64)
--
-- Host: localhost    Database: db_sluiceGate
-- ------------------------------------------------------
-- Server version	5.7.39-0ubuntu0.18.04.2

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
-- Table structure for table `salinity`
--

DROP TABLE IF EXISTS `salinity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `salinity` (
  `idsalinity` int(11) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `salinity` double NOT NULL,
  PRIMARY KEY (`idsalinity`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `salinity`
--

LOCK TABLES `salinity` WRITE;
/*!40000 ALTER TABLE `salinity` DISABLE KEYS */;
INSERT INTO `salinity` VALUES (1,'2022-08-16 14:47:01',20.55),(2,'2022-08-16 14:47:11',21.05),(3,'2022-08-16 14:47:21',21),(4,'2022-08-16 14:47:31',20.8),(5,'2022-08-16 14:47:41',20.55),(6,'2022-08-16 14:47:51',20.25),(7,'2022-08-16 14:48:01',19.9),(8,'2022-08-16 14:48:11',19.8),(9,'2022-08-16 14:48:21',19.5),(10,'2022-08-16 14:48:31',19.200000000000003),(11,'2022-08-16 14:48:41',18.950000000000003),(12,'2022-08-16 14:48:51',19),(13,'2022-08-16 14:49:01',18.95);
/*!40000 ALTER TABLE `salinity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `water_level_landside`
--

DROP TABLE IF EXISTS `water_level_landside`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `water_level_landside` (
  `idwater_level_landside` int(11) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `water_level` double NOT NULL,
  PRIMARY KEY (`idwater_level_landside`)
) ENGINE=InnoDB AUTO_INCREMENT=98 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `water_level_landside`
--

LOCK TABLES `water_level_landside` WRITE;
/*!40000 ALTER TABLE `water_level_landside` DISABLE KEYS */;
INSERT INTO `water_level_landside` VALUES (1,'2022-08-16 14:18:13',2),(2,'2022-08-16 14:18:18',2.1),(3,'2022-08-16 14:18:18',2),(4,'2022-08-16 14:18:21',2.2),(5,'2022-08-16 14:18:22',2.2),(6,'2022-08-16 14:18:22',2.3),(7,'2022-08-16 14:18:23',2.4),(8,'2022-08-16 14:18:25',2.6),(9,'2022-08-16 14:18:26',2.5),(10,'2022-08-16 14:18:29',2.7),(11,'2022-08-16 14:18:29',2.7),(12,'2022-08-16 14:18:34',2.6),(13,'2022-08-16 14:18:36',2.7),(14,'2022-08-16 14:18:40',2.8),(15,'2022-08-16 14:18:41',3),(16,'2022-08-16 14:18:41',2.8),(17,'2022-08-16 14:18:42',3.2),(18,'2022-08-16 14:18:43',3.3),(19,'2022-08-16 14:18:44',2.5),(20,'2022-08-16 14:18:47',2.8),(21,'2022-08-16 14:18:51',2.8),(22,'2022-08-16 14:18:52',3.2),(23,'2022-08-16 14:18:53',2.9),(24,'2022-08-16 14:18:53',3),(25,'2022-08-16 14:18:56',2.8),(26,'2022-08-16 14:18:57',2.8),(27,'2022-08-16 14:18:58',2.9),(28,'2022-08-16 14:19:01',3),(29,'2022-08-16 14:19:02',2.8),(30,'2022-08-16 14:19:03',2.8),(31,'2022-08-16 14:19:05',3),(32,'2022-08-16 14:19:06',3.1),(33,'2022-08-16 14:19:08',3.3),(34,'2022-08-16 14:19:08',3.2),(35,'2022-08-16 14:19:13',3.4),(36,'2022-08-16 14:19:14',3.6),(37,'2022-08-16 14:19:20',3.8),(38,'2022-08-16 14:19:23',3.4),(39,'2022-08-16 14:19:27',3.6),(40,'2022-08-16 14:19:27',4),(41,'2022-08-16 14:19:28',3.8),(42,'2022-08-16 14:19:28',4),(43,'2022-08-16 14:19:30',3.7),(44,'2022-08-16 14:19:30',4.2),(45,'2022-08-16 14:19:31',3.8),(46,'2022-08-16 14:19:31',4.5),(47,'2022-08-16 14:19:32',4),(48,'2022-08-16 14:19:34',3.8),(49,'2022-08-16 14:19:37',4.1),(50,'2022-08-16 14:19:37',4.6),(51,'2022-08-16 14:19:38',4.4),(52,'2022-08-16 14:19:40',4.2),(53,'2022-08-16 14:47:03',2),(54,'2022-08-16 14:47:05',2.2),(55,'2022-08-16 14:47:09',2.4),(56,'2022-08-16 14:47:14',2.7),(57,'2022-08-16 14:47:16',2.8),(58,'2022-08-16 14:47:19',2.9),(59,'2022-08-16 14:47:21',3.1),(60,'2022-08-16 14:47:22',3.2),(61,'2022-08-16 14:47:26',3.4),(62,'2022-08-16 14:47:27',3.3),(63,'2022-08-16 14:47:28',3.1),(64,'2022-08-16 14:47:29',2.9),(65,'2022-08-16 14:47:39',3),(66,'2022-08-16 14:47:41',2.7),(67,'2022-08-16 14:47:45',3),(68,'2022-08-16 14:47:46',2.7),(69,'2022-08-16 14:47:49',2.9),(70,'2022-08-16 14:47:54',3),(71,'2022-08-16 14:47:55',2.8),(72,'2022-08-16 14:48:02',2.7),(73,'2022-08-16 14:48:03',3),(74,'2022-08-16 14:48:04',2.9),(75,'2022-08-16 14:48:05',3.2),(76,'2022-08-16 14:48:06',3.1),(77,'2022-08-16 14:48:07',2.9),(78,'2022-08-16 14:48:32',3.1),(79,'2022-08-16 14:48:33',2.9),(80,'2022-08-16 14:48:34',3.1),(81,'2022-08-16 14:48:35',2.9),(82,'2022-08-16 14:48:36',2.8),(83,'2022-08-16 14:48:42',3),(84,'2022-08-16 14:48:43',2.9),(85,'2022-08-16 14:48:44',3),(86,'2022-08-16 14:48:45',2.8),(87,'2022-08-16 14:48:49',2.7),(88,'2022-08-16 14:48:54',2.7),(89,'2022-08-16 14:48:55',3),(90,'2022-08-16 14:48:56',2.9),(91,'2022-08-16 14:48:58',3),(92,'2022-08-16 14:48:59',2.8),(93,'2022-08-16 14:49:03',3),(94,'2022-08-16 14:49:04',2.9),(95,'2022-08-16 14:49:06',3),(96,'2022-08-16 14:49:07',2.8),(97,'2022-08-16 14:49:10',2.6);
/*!40000 ALTER TABLE `water_level_landside` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-09-08 12:00:18
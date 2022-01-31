-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost
-- Tiempo de generación: 09-12-2021 a las 21:49:37
-- Versión del servidor: 5.7.36-cll-lve
-- Versión de PHP: 7.4.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `alzowxrz_libreria`
--

DELIMITER $$
--
-- Procedimientos
--
DROP PROCEDURE IF EXISTS `getBookInfo`$$
CREATE DEFINER=`alzowxrz`@`localhost` PROCEDURE `getBookInfo` (IN `iId` INT(15) UNSIGNED)  SELECT * FROM catalogo WHERE id=iId$$

DROP PROCEDURE IF EXISTS `getLibrosComprados`$$
CREATE DEFINER=`alzowxrz`@`localhost` PROCEDURE `getLibrosComprados` (IN `iId` INT(10))  SELECT id_usuario,id_libro,titulo,autor,genero,descripcion,precio,img FROM compras LEFT JOIN catalogo on compras.id_libro=catalogo.id WHERE compras.id_usuario=iId$$

DROP PROCEDURE IF EXISTS `insertCompra`$$
CREATE DEFINER=`alzowxrz`@`localhost` PROCEDURE `insertCompra` (IN `iUsuario` INT(10), IN `iLibro` INT(10))  INSERT INTO compras (id_usuario,id_libro) 
VALUES(iUsuario,iLibro)$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `catalogo`
--

DROP TABLE IF EXISTS `catalogo`;
CREATE TABLE IF NOT EXISTS `catalogo` (
  `id` int(2) NOT NULL AUTO_INCREMENT,
  `titulo` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `autor` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `precio` float NOT NULL,
  `genero` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `descripcion` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `img` varchar(25) COLLATE utf8mb4_unicode_ci NOT NULL,
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `catalogo`
--

INSERT INTO `catalogo` (`id`, `titulo`, `autor`, `precio`, `genero`, `descripcion`, `img`) VALUES
(1, 'El señor de los anillos: La comunidad del anillo', 'J.R.R. Tolkien', 11.99, 'Fantasia', 'En la adormecida e idílica Comarca, un joven hobbit recibe un encargo: custodiar el Anillo Único y emprender el viaje para su destrucción en las Grietas del Destino. Consciente de la importancia de su misión, Frodo abandona la Comarca e inicia el camino hacia Mordor con la compañía inesperada de Sam, Pippin y Merry.', ''),
(2, 'El señor de los anillos: Las dos torres', 'J.R.R. Tolkien', 11.99, 'Fantasia', 'En la búsqueda para destruir el Anillo Único, la comunidad ha quedado disuelta. Frodo y Sam descubren que están siendo seguidos por el misterioso Gollum.', ''),
(3, 'El señor de los anillos: El retorno del rey', 'J.R.R. Tolkien', 13.99, 'Fantasia', 'El ejército de Sauron ha atacado Minas Tirith, la capital de Gondor. Una poderosa amenaza pone en peligro la paz del reino, antaño poderoso y que ahora necesita más que nunca a su rey.', ''),
(4, 'Las Cronicas de Narnia: El leon, la bruja y el armario', 'C. S. Lewis', 21.99, 'Magia', 'Cuatro niños descubren que un armario oculta mucho más que prendas de ropa. Se trata de una puerta a un mundo totalmente desconocido: Narnia.', ''),
(5, 'Las Cronicas de Narnia: El principe Caspian', 'C. S. Lewis', 18.99, 'Magia', 'El príncipe lucha por su corona, al tiempo que descubre la verdadera historia de su pueblo, los telmarinos, unos auténticos piratas terrestres… Los Pevensie acuden a Narnia de nuevo para ayudar al príncipe a recuperar el trono.', ''),
(6, 'Las Cronicas de Narnia: La travesia del Viajero del Alba', 'C. S. Lewis', 40.99, 'Magia', 'El libro relata las aventuras vividas por Edmund y Lucy Pevensie, junto a su primo Eustace Scrubb a bordo del barco El Viajero del Alba o Explorador del Amanecer', ''),
(7, 'Nacidos de la bruma: El imperio final', 'Brandon Sanderson', 15.99, 'Ciencia Ficcion', 'Durante mil años han caído las cenizas y nada florece. Durante mil años los skaa han sido esclavizados y viven sumidos en un miedo inevitable. Durante mil años el Lord Legislador reina con un poder absoluto gracias al terror, a sus poderes e inmortalidad. Le ayudan «obligadores» e «inquisidores», junto a la poderosa magia de la «alomancia».', '');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `compras`
--

DROP TABLE IF EXISTS `compras`;
CREATE TABLE IF NOT EXISTS `compras` (
  `id_compra` int(11) NOT NULL AUTO_INCREMENT,
  `id_usuario` int(11) DEFAULT NULL,
  `id_libro` int(11) DEFAULT NULL,
  `fecha` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id_compra`),
  KEY `id_libro` (`id_libro`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Volcado de datos para la tabla `compras`
--

INSERT INTO `compras` (`id_compra`, `id_usuario`, `id_libro`, `fecha`) VALUES
(9, 19, 2, '2021-12-08 22:33:58'),
(15, 19, 1, '2021-12-09 20:45:32'),
(16, 19, 4, '2021-12-09 20:45:32'),
(17, 19, 5, '2021-12-09 20:45:32');

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `compras`
--
ALTER TABLE `compras`
  ADD CONSTRAINT `compras_ibfk_1` FOREIGN KEY (`id_libro`) REFERENCES `catalogo` (`id`) ON DELETE SET NULL ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

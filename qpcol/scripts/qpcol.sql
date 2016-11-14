PRAGMA encoding = "UTF-8";
PRAGMA foreign_keys = true;

DROP TABLE IF EXISTS `film_tag`;
DROP TABLE IF EXISTS `film`;
DROP TABLE IF EXISTS `tag`;

CREATE TABLE IF NOT EXISTS `film` (
  `id_film` INTEGER PRIMARY KEY AUTOINCREMENT,
  `hash` varchar(32) COLLATE BINARY NOT NULL UNIQUE,
  `filepath` varchar(600) COLLATE BINARY NOT NULL,
  `filename` varchar(255) COLLATE BINARY NOT NULL,
  `size` int(11) NOT NULL,
  `original_filepath` varchar(600) COLLATE BINARY NOT NULL,
  `original_url` varchar(600) DEFAULT NULL,
  `blacklist` boolean NOT NULL DEFAULT '0',
  `favorite` boolean NOT NULL DEFAULT '0',
  `marked` boolean NOT NULL DEFAULT '0',
  `added_when` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `notes` varchar(4096) DEFAULT NULL COLLATE NOCASE
);

CREATE INDEX `idx_filename` ON `film` (`filename`);

CREATE TABLE IF NOT EXISTS `tag` (
  `id_tag` INTEGER PRIMARY KEY AUTOINCREMENT,
  `tag` varchar(50) COLLATE NOCASE NOT NULL UNIQUE
);

CREATE INDEX `idx_tag` ON `tag` (`tag`);

CREATE TABLE IF NOT EXISTS `film_tag` (
  `id_film` INTEGER NOT NULL,
  `id_tag` INTEGER NOT NULL,
  CONSTRAINT `fk_id_film` FOREIGN KEY (`id_film`) REFERENCES `film` (`id_film`) ON DELETE CASCADE,
  CONSTRAINT `fk_id_tag` FOREIGN KEY (`id_tag`) REFERENCES `tag` (`id_tag`) ON DELETE CASCADE,
  CONSTRAINT `unique_film_tag` UNIQUE (`id_film`, `id_tag`)
);

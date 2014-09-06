CREATE TABLE IF NOT EXISTS `sensors` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `humidity` int(11) NOT NULL COMMENT '%',
  `temperature` int(11) NOT NULL COMMENT '°C',
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- @block Bookmarked query
-- @group Ungrouped
-- @name create_student
--@blok CREATE TABLE STUDENT
--@conn mariadb
CREATE TABLE IF NOT EXISTS `STUDENT` (
    `id` INT UNSIGNED AUTO_INCREMENT,
    `name` VARCHAR(10) NOT NULL,
    `gender` VARCHAR(1) NOT NULL,
    `age` INT UNSIGNED,
    PRIMARY KEY (`id`)
);
INSERT INTO STUDENT(0, '张三', '1', 12);
SELECT *
FROM test.STUDENT;
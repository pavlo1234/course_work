
--створення бази даних
CREATE DATABASE MessageApp;
USE MessageApp;

-- створення таблиці користувачів
CREATE TABLE Users(
    login VARCHAR(255) PRIMARY KEY,
    -- створення поля email унікальним для кожного запису
    email VARCHAR(255) NOT NULL UNIQUE, 
    pswd VARCHAR(255) NOT NULL
);

-- створення таблиці чатів
CREATE TABLE Chats(
	id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(255) NOT NULL,
    creator VARCHAR(255) NOT NULL
);

-- створенн таблиці повідомлень
CREATE TABLE Messages(
	id INT PRIMARY KEY auto_increment,
    cid INT NOT NULL,
    login VARCHAR(255) NOT NULL,
    mtext VARCHAR(255) NOT NULL,
    mtime DATETIME NOT NULL,
    FOREIGN KEY (cid) REFERENCES Chats(id) ON UPDATE NO ACTION ON DELETE CASCADE,
    FOREIGN KEY (login) REFERENCES Users(login) ON UPDATE CASCADE ON DELETE NO ACTION,
    -- створення індексу за атрибутом дати та часу відправлення 
    INDEX time_idx(mtime)
);

-- створення таблиці для позначення відношень між користувачами та чатами
CREATE TABLE Users_Chats(
	id INT PRIMARY KEY AUTO_INCREMENT,
    login VARCHAR(255) NOT NULL,
    cid INT NOT NULL,
    FOREIGN KEY (login) REFERENCES Users(login) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (cid) REFERENCES Chats(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- створення таблиці для позначення відношень заборони між користувачами
CREATE TABLE Users_BL(
	id INT PRIMARY KEY AUTO_INCREMENT,
    -- поле логіну користувача-блокувальника
    login_blocker VARCHAR(255) NOT NULL,
    -- поле логіну заблокованого користувача
    login_blocked VARCHAR(255) NOT NULL,
    FOREIGN KEY (login_blocker) REFERENCES Users(login) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (login_blocked) REFERENCES Users(login) ON DELETE CASCADE ON UPDATE CASCADE
);

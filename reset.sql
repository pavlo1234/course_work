USE messageapp;
DELETE FROM users_chats WHERE id > 0;
ALTER TABLE users_chats auto_increment = 0;
DELETE FROM messages WHERE id > 0;
ALTER TABLE messages auto_increment = 0;
DELETE FROM chats WHERE id > 0;
ALTER TABLE chats auto_increment = 0;
DELETE FROM users_bl WHERE id > 0;
ALTER TABLE users_bl auto_increment = 0;
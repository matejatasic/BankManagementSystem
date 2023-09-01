CREATE TABLE IF NOT EXISTS accounts (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, owner varchar(30) NOT NULL, pin varchar(50) NOT NULL, phone varchar(16) NOT NULL, email varchar(30) NOT NULL, registration_date date NOT NULL, balance decimal);
CREATE TABLE IF NOT EXISTS employees (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, username varchar(30) NOT NULL, password varchar(200) NOT NULL, phone varchar(16) NOT NULL, position varchar(15) NOT NULL);
CREATE TABLE IF NOT EXISTS transactions(id integer NOT NULL PRIMARY KEY AUTOINCREMENT,amount decimal, account_id integer, type varchar(30), datetime datetime, FOREIGN KEY(account_id) REFERENCES accounts(id));

INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer', '1754688', '1234567890', 'test@test.com', '2023-02-03', 1000.00);
INSERT INTO employees (username, password, phone, position) VALUES ('Admin', '1599742', '1234567890', 'admin');
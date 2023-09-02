CREATE TABLE IF NOT EXISTS accounts (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, owner varchar(30) NOT NULL, pin varchar(50) NOT NULL, phone varchar(16) NOT NULL, email varchar(30) NOT NULL, registration_date date NOT NULL, balance decimal);
CREATE TABLE IF NOT EXISTS employees (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, username varchar(30) NOT NULL, password varchar(200) NOT NULL, phone varchar(16) NOT NULL, position varchar(15) NOT NULL);
CREATE TABLE IF NOT EXISTS transactions(id integer NOT NULL PRIMARY KEY AUTOINCREMENT,amount decimal, account_id integer, type varchar(30), datetime datetime, FOREIGN KEY(account_id) REFERENCES accounts(id));


-- Insert entries into the accounts table
-- The pin for all of them is 1234
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer', '1599742', '1234567890', 'test@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer1', '1599742', '1234567891', 'test1@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer2', '1599742', '1234567892', 'test2@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer3', '1599742', '1234567893', 'test3@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer4', '1599742', '1234567894', 'test4@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer5', '1599742', '1234567895', 'test5@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer6', '1599742', '1234567896', 'test6@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer7', '1599742', '1234567897', 'test7@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer8', '1599742', '1234567898', 'test8@test.com', '2023-02-03', 1000.00);
INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES ('Customer9', '1599742', '1234567899', 'test9@test.com', '2023-02-03', 1000.00);

-- Insert entries into the accounts table
-- The password for all of them is 1234
INSERT INTO employees (username, password, phone, position) VALUES ('Admin', '1599742', '1234567890', 'admin');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee1', '1599742', '1234567891', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee2', '1599742', '1234567892', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee3', '1599742', '1234567893', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee4', '1599742', '1234567894', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee5', '1599742', '1234567895', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee6', '1599742', '1234567896', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee7', '1599742', '1234567897', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee8', '1599742', '1234567898', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee9', '1599742', '1234567899', 'teller');
INSERT INTO employees (username, password, phone, position) VALUES ('Employee0', '1599742', '1234567890', 'teller');
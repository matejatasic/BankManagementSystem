# Overview
This is the final project for the CS50's Introduction to Computer Science course. This is a Bank management system console app with some basic customer functionalities written in C++. At first it was planned to be written in C, but after considering the complexity of the application it was decided to be rewritten in C++. Admin and teller part of the application were also planned to be built, but after estimating the complexity of adding those parts, it was decided to create only the basic customer functionalities, but those parts may be added in the future. After a while, afther getting the CS50X certificate, the admin part was added. Refactoring is planned in the future. 

# Basic functionalities
## Customer Part
1. Account information
2. Money depositing
3. Money withdrawing
4. Transaction details
5. Pin change
6. Personal details change

## Admin part
1. All accounts information
2. All employees information
3. Individual account information
4. Individual employee information
5. Create account
6. Update account
7. Delete account
8. Create employee
9. Update employee
10. Delete employee
11. Show transactions for an account

# Usage
1. Download the project
2. Install the needed packages by running `sudo apt-get install sqlite3 libsqlite3-dev`
3. In the project folder run `make`
4. Enter sqlite shell by running `sqlite3 bank-management-system.db`
5. Paste the SQL commands from bank-management-system.sql, hit Enter and then hit `CTRL + D` to exit
6. After that run the executable using the `./bank-management-system` command

## About CS50
CS50 is a openware course from Havard University and taught by David J. Malan

Introduction to the intellectual enterprises of computer science and the art of programming. This course teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, and software engineering. Languages include C, Python, and SQL plus students’ choice of: HTML, CSS, and JavaScript (for web development).

- Where do I get CS50 course?
https://cs50.harvard.edu/x/2020/

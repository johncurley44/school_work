/* -------------------------\
!	John Curley-16013276	!
!	Lab: 9:00AM Tues. 		!
!	TA: John Benjamin		!
!	Assignment: Lab4		!
!	Due: 9/21/2013			!
\--------------------------*/



CREATE SCHEMA lab4;

SET search_path = lab4;
	
	CREATE TABLE customer(
		cust_id SERIAL PRIMARY KEY,
		poc_name varchar(50),
		shipping_address varchar(50)
	);
	
	CREATE TABLE invoice(
		cust_id integer REFERENCES customer,
		inv_no SERIAL PRIMARY KEY,
		invoice_date date
	);
	
	CREATE TABLE product(
		product_id SERIAL PRIMARY KEY,
		name varchar(50)
	);
	
	CREATE TABLE invoiceLine(
		inv_no integer REFERENCES invoice,
		product_id integer REFERENCES product UNIQUE,
		line_number integer NOT NULL,
		quantity integer,
		price integer,
		PRIMARY KEY(inv_no, product_id, line_number)
	);
	
	CREATE TABLE factory(
		factory_id SERIAL PRIMARY KEY,
		phone_number integer
	);
	
	CREATE TABLE makes(
		product_id integer REFERENCES product,
		factory_id integer REFERENCES factory,
		PRIMARY KEY (product_id, factory_id)
	);
	
	CREATE TABLE employee(
		factory_id integer REFERENCES factory UNIQUE,
		employee_id SERIAL PRIMARY KEY,
		first_name varchar(25),
		last_name varchar(25)
	);
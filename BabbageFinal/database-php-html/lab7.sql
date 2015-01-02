/* -------------------------\
!	John Curley-16013276	!
!	Lab: 9:00AM Tues. 		!
!	TA: John Benjamin		!
!	Assignment: Lab7		!
!	Due: 10/13/2013			!
\--------------------------*/




--TAKE OUT DROP TABLES STUFF SEE LAB4

CREATE SCHEMA lab7;

SET search_path = lab7;	
	
	CREATE TABLE standings(
		team varchar (40) PRIMARY KEY,
		wins integer,
		losses integer,
		winning_percentage float(3),
		CHECK (wins>=0 AND losses>=0 AND winning_percentage>=0 AND winning_percentage<=1)
	);
	
	INSERT INTO standings VALUES ('St. Louis', 97, 65, 0.599);
	INSERT INTO standings VALUES ('Pittsburgh', 94, 68, 0.580);
	INSERT INTO standings VALUES ('Cincinatti', 90, 72, 0.556);
	INSERT INTO standings VALUES ('Milwaukee', 74, 88, 0.457);
	INSERT INTO standings VALUES ('Chicago', 66, 96, 0.407);
	
	SELECT * FROM standings;
	
	--Function for calculating winning percentage
	CREATE OR REPLACE FUNCTION calc_winning_percentage(integer, integer) RETURNS float AS $$
		SELECT ROUND((($1 :: float)/ ($1+$2))::numeric,3)::float AS result;
	$$ LANGUAGE SQL;
	--Trigger for when update or insert command detected
	CREATE OR REPLACE FUNCTION update_winning_percentage() RETURNS trigger AS $$
	BEGIN 
	--Debugging info
		IF 'UPDATE' = TG_OP THEN
			RAISE NOTICE 'OLD.wins = %', OLD.wins;
			RAISE NOTICE 'OLD.losses = %', OLD.losses;
		END IF;
		RAISE NOTICE 'NEW.wins = %', NEW.wins;
		RAISE NOTICE 'NEW.losses = %', NEW.losses;
		RAISE NOTICE 'TG_OP = %', TG_OP;
	--For updates, check to make sure new update isn't violating winning percentage explicitly, if not, set new winning percentage via calc_winning_percentage
		IF('UPDATE' = TG_OP) THEN	
			IF(NEW.winning_percentage <> OLD.winning_percentage AND NEW.winning_percentage <> calc_winning_percentage(NEW.wins, NEW.losses)) THEN
				RAISE EXCEPTION 'Winning Percentage must be equal to (wins/(games played))';
			END IF;
			NEW.winning_percentage := calc_winning_percentage(NEW.wins, NEW.losses);
		END IF;
	--For insert commands, make sure chosen winning percentage is correct.
		IF('INSERT' = TG_OP) THEN
			IF(NEW.winning_percentage <> calc_winning_percentage(NEW.wins, NEW.losses)) THEN
				RAISE EXCEPTION 'Winning Percentage must be equal to (wins/(games played))';
			END IF;
		END IF;
		
		RETURN NEW;
	END;
	$$ LANGUAGE plpgsql;
	--Create the trigger
	CREATE TRIGGER tr_lab7_uwp BEFORE INSERT OR UPDATE ON standings FOR EACH ROW EXECUTE PROCEDURE update_winning_percentage();

		
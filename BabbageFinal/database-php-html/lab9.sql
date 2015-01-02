/* -------------------------\
!	John Curley-16013276	!
!	Lab: 9:00AM Tues. 		!
!	TA: John Benjamin		!
!	Assignment: Lab9		!
!	Due: 11/3/2013			!
\--------------------------*/ 

SET search_path = lab9, public;

--Question 1: 
SELECT stateone.name10 FROM lab9.tl_2010_us_state10 AS stateone WHERE ST_Intersects(stateone.coords, ST_SetSRID(ST_MakeBox2D(ST_Point(-98, 39),ST_Point(-90, 43)),4326)) ORDER BY stateone.name10 ASC;

--Question 2:
SELECT statetwo.stusps10, statetwo.name10 FROM lab9.tl_2010_us_state10 AS stateone, lab9.tl_2010_us_state10 AS statetwo WHERE stateone.stusps10 = 'CO' AND ST_Touches(stateone.coords, statetwo.coords) ORDER BY statetwo.name10 ASC; 

--Question 3:
SELECT urbanone.name10 FROM lab9.tl_2010_us_state10 AS stateone, lab9.tl_2010_us_uac10 AS urbanone WHERE stateone.stusps10 = 'MO' AND ST_Contains(stateone.coords, urbanone.coords);

--Question 4:
SELECT urbanone.name10, (urbanone.aland10 + urbanone.awater10)/1000000 AS sum_land_water FROM lab9.tl_2010_us_state10 AS stateone, lab9.tl_2010_us_uac10 AS urbanone WHERE stateone.stusps10 = 'IL' AND ST_Overlaps(stateone.coords, urbanone.coords) ORDER BY sum_land_water DESC;

--Question 5:
SELECT urbanone.name10 AS city_A, urbantwo.name10 AS city_B FROM lab9.tl_2010_us_uac10 AS urbanone, lab9.tl_2010_us_uac10 AS urbantwo WHERE ST_Intersects(urbanone.coords, urbantwo.coords) AND urbanone.gid < urbantwo.gid;

--Question 6:
SELECT urbanone.name10, COUNT(DISTINCT stateone.name10) AS num_states_intersected FROM lab9.tl_2010_us_uac10 AS urbanone, lab9.tl_2010_us_state10 AS stateone, lab9.tl_2010_us_state10 AS statetwo WHERE ((urbanone.aland10 + urbanone.awater10)/1000000) > 1000 AND ST_Intersects(urbanone.coords, stateone.coords) AND ST_Intersects(urbanone.coords, statetwo.coords) AND stateone.name10 != statetwo.name10 GROUP BY urbanone.name10 ORDER BY num_states_intersected DESC, urbanone.name10 ASC;
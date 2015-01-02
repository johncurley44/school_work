<html>
<head/>
<body>
<form method="POST" action="<?= $_SERVER['PHP_SELF'] ?>">
  <table border="1">
     <tr><td>Number of Rows:</td><td><input type="text" name="rows" /></td></tr>
     <tr><td>Number of Columns:</td><td><select name="columns">
    <option value="1">1</option>
    <option value="2">2</option>
    <option value="4">4</option>
    <option value="8">8</option>
    <option value="16">16</option>

  </select>
</td></tr>
   <tr><td>Operation:</td><td><input type="radio" name="operation" value="multiplication" checked="yes">Multiplication</input><br/>
  <input type="radio" name="operation" value="addition">Addition</input>
  </td></tr>
  </tr><td colspan="2" align="center"><input type="submit" name="submit" value="Generate" /></td></tr>
</table>
</form>

<?php

    /***************************\
	!	John Curley-16013276	!
	!	Lab: 9:00AM Tues. 		!
	!	TA: John Benjamin		!
	!	Assignment: Lab1		!
	!	Due: 8/29/2013			!
	\***************************/
	
   // Checks to see if the 'Generate' button has been pressed
   if ( isset( $_POST['submit'] ) ) {
		$rows = htmlspecialchars( $_POST['rows'] );
		$columns = htmlspecialchars( $_POST['columns'] );
		$operation = htmlspecialchars( $_POST['operation']);
		echo 'The '.$rows.' x '.$columns.' '.$operation.' table.';
		//Ensures that the user input 'rows' is positive and a numeric value
		if($rows>0 && is_numeric($rows)){
			// Formats a basic table
			echo '<table cellpadding="1" cellspacing="2" class="db-table" border="1" style="text-align:center">';
			echo '<tr>';
			// Prints the column numbers in bold as first row
			for($k=0; $k <= $columns; $k++){
				echo '<td><strong>'.$k.'</strong></td>';
			}
			echo "</tr>";
			// Checks if table is to be a multiplication table based on radio button user input
			if($_POST['operation']=='multiplication'){
				// Iterates through rows
				for($i=0; $i < $rows; $i++){
					// Prints row number in bold
					echo '<tr><td><strong>'.($i+1).'</strong></td>';
					// Iterates through columns, printing result of multiplication in each cell
					for($j = 0; $j < $columns; $j++){
						echo '<td>'.($j+1)*($i+1).'</td>';
					}
					echo'</tr>';
				}
			}
			// Checks if table is to be an addition table based on radio button user input
			elseif($_POST['operation']=='addition'){
				//Iterates through rows
				for($i=0; $i < $rows; $i++){
					// Prints row number in bold
					echo '<tr><td><strong>'.($i+1).'</strong></td>';
					// Iterates through columns, printing result of addition in each cell
					for($j = 0; $j < $columns; $j++){
						echo '<td>'.(($j+1)+($i+1)).'</td>';
					}
					echo'</tr>';
				}
			}
			// Problem in code. Neither addition or multiplication options were chosen.
			else{
				echo 'Error. Addition or multiplication must be chosen.';
			}
			echo'</tr>';
		}
		// If 'rows' is not a numeric value, prints an error message
		elseif(is_numeric($rows) == false){
			echo 'Rows must be a numeric value. Please retry.';
		}
		// If 'rows' is not positive, prints an error message
		elseif($rows<=0){
			echo 'Rows must be greater than 0. Please retry.';
		}
		// If this is reached, there must be an error in coding. Both 'if' conditions covered in 'elseif's
		else{
			echo 'Rows seems to be numeric and greater than 0. Please check code.';
		}
	}
		
?>
</body>
</html>
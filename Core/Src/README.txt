
/*******************************************************************************************************************************************************************************************************************/

Date : 25/09/2024
Author : Aman Singh

-> Facing the problem in the GNSS module pin in which when we connect the board with the debugger it take the right value from the module but when we applied the power then it start showing the 
Alien language trying method:
1- Review the code 
2- Changing the resistance for checking the power with it.
3- Remove the R3 resistance 
4- Touch each section again 
5- Replace the cap and res again
6- Checking the micro tx and rx pin<This is an issue it pins is not working properly>

->Resistance with same intensity is making by changing the value of the resistance with 33E.

->Then checking the Gnss Module with sending the command to it but NOT GETTING ANY RESPONSE -> Checking by sending the command with micro but not getting response.
BUT ITS BAUD RATE CHANGES FROM THE 115200 TO 9600 SO I CHANGED THE ONLY BAUDRATE TO THE OLD CODE WHICH IS WORKING PROPERLY.


/******************************************************************************************************************************************************************************************************************/


Date : 26/09/2024
Author : Aman Singh

-> Facing the bug again that code might be stuck in some case so , ADDING THE IWDG in the new code<9600 Baud Rate> with the prescalar 32 not changing anything else <<VALIDATION_IS_PENDING>>
changes is done the previous working code is :
                                          a - Changes the baudrate from 115200 to 9600  <Because the baud rate changes by module lastly I changed >
                                          b - <Adding the iwdg>.
                         
                         
/******************************************************************************************************************************************************************************************************************/

Date : 03/10/2024
Author : Aman Singh

-> When added the iwdg in the given code then after it checked thrice it is not showing the any issue the after till now <15:40pm>

/******************************************************************************************************************************************************************************************************************/
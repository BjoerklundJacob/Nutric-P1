# VeGen-P1
Repository for P1 - Software19

Hello and welcome to Nutric, during this text you will learn to use and manage the files and programs involved in Nutric. 

DISCLAIMER: The program is Windows 10 and Windows XP or earlier only!!!!


The first thing to do when using the program is opening the file:
	Nutric.exe - This file is found in the Nutric-p1 folder.

When this file is opened you will be greeted by:
	     __       _        _
	  /\ \ \_   _| |_ _ __(_) ___
	 /  \/ / | | | __| '__| |/ __|
	/ /\  /| |_| | |_| |  | | (__
	\_\ \/  \__,_|\__|_|  |_|\___|
	(1) Nutrients
	(2) User Settings
	(3) Open the recipe list
	(0) Exit

The parentheses and numbers correspond to the number on your heyboard you should press to access the different parts of the program.

The first button the user should consider pressing the 2 button.

This button will open the user settings, where you have access to some options where you can change your gender, age and, weight.
These options is recommended that you set, because it will give you a more correct output, but it is not essential.

The next thing the user should consider is pressing the 3 button, which will open the input.json file and allow you to input your meals for the day in the json database format.
This may sound scary, but the json file format is quite easy.
Each recipe needs to be placed in between quotations marks in such a manner:
	"50 g my ingredient"
First an amount is needed this can be both a whole or decimal number, the decimal seperator is a: .
Next is the unit, we recommend basic units used in the kitchen such as g and kg, but the program supports many units a full list can be seen at the bottom of the document.

Lastly a ingredient or meal is needed this can be more or less specific, the program will give you up to 5 options it thinks your ingredient or meal might be you should then choose the correct one, if none of the options are correct, you should go back and open the file and change to be more or less specific depending on what you originally wrote, say you wrote:
	"50 g hershee's dark chocolate 56% organic for cooking"

If this is the case and you get no results we recommend a simpler search such as: "50 g dark chocolate"

another example could be: "50 g chocolate"
You might get 5 good offers, but if you needed dark chocolate it might only give you light, so a more specific search is recommended.

Now the file allows for more added recipies or meals, it is important that you seperate these with commas. ,
As seen below:
			"50 g dark chocolate",
			"50 kg carrot"

The last element should NOT have a comma at the end.

Pressing the number one button will load the file: input.json
	The file will be read and the nutrients counter and outputted to
	the screen.

Lastly the 0 button closes the program!

Now enjoy the program! If you have any issues email: support@nutric.com

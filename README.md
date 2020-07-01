# ParsingJSONUsingCFromPanther
Sample code on how to parse JSON data using C from Panther. JSON data is sent from a caller screen to servicescreen.jam screen which sends a response back to the first screen as a parsed JSON data with the help of a C function.  

# Prerequisites
Panther Web 5.5*

# This repository consists of 5 files
* Panther screen name caller
* Panther screen name servicescreen.jam
* funclist.c
* caller.html
* servicescreen.html


# Caller screen
Contains a Panther push button from which a JavaScript function is executed from  the on_click property  

# Servicescreen screen
Contains 2 single line text fields and 2 multiline text fields. One MLT is used to get JSON data from the caller screen and the other MLT gets JSON parsed data from the C function. In the JPL in web_enter function is executing the C function that parses the JSON data.

# Funclist.c
Consist that the functions below that  parses the JSON data. To use this feature please rebuild your JServer using the funclist.c that consist specific C code.    
static	int	walk_jsmn	PROTO((char *, jsmntok_t *, char *, int, jsmn_callback_t f));
static	int	jsmn_putfield	PROTO((char *fieldname, char *value, int occur));

# Caller.html
HTML template is attached to the Panther caller screen via property WEB OPTION->HTML OPTIONs->HTML Template. It consist of a JavaScript function called from the on_click property of a push button. The function also makes an AJAX call to send JSON data to the servicescreen.jam. 

# Servicescreen.html
Panther caller that consist of raw MLT property to get the response.

Need a Panther Web 552 Redhat Image? [Click Here](https://hub.docker.com/r/prolificspanther/pantherweb "Named link title") 

How to set up a Panther Servlet Web Application? [Click Here](https://github.com/ProlificsPanther/PantherWeb/releases "Named link title")

Read our Documentation [here](https://docs.prolifics.com)

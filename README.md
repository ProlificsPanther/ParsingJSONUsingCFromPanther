# ParsingJSONUsingCFromPanther
Sample code to parse JSON data using C from Panther. JSON data is sent from a caller screen to servicescreen.jam screen which sends a response back to the first screen as parsed JSON data with the help of a C function.  

# Prerequisites
Panther Web 5.5*

# This repository consists of 5 files
* Panther screen name caller
* Panther screen name servicescreen.jam
* funclist.c
* caller.html
* servicescreen.html


# Caller screen
 Executes on_click  JavaScript function   from pushbutton

# Servicescreen screen
 One MLT gets JSON data from the caller screen and the other MLT gets JSON parsed data from the C function. JPL in the web_enter() function executes the C function that parses the JSON data.

# Funclist.c
Consist of functions below that  parses the JSON data. To use this feature please rebuild your JServer with these C functions.    
static	int	walk_jsmn	PROTO((char *, jsmntok_t *, char *, int, jsmn_callback_t f));
static	int	jsmn_putfield	PROTO((char *fieldname, char *value, int occur));

# Caller.html
HTML template is attached to the Panther caller screen via property WEB OPTION->HTML OPTIONs->HTML Template. It consist of a JavaScript function called from the on_click property of a push button. The function also makes an AJAX call to send JSON data to servicescreen.jam. 

# Servicescreen.html
Consist of raw MLT property to get the response.

Need a Panther Web 552 Redhat Image? [Click Here](https://hub.docker.com/r/prolificspanther/pantherweb "Named link title") 

How to set up a Panther Servlet Web Application? [Click Here](https://github.com/ProlificsPanther/PantherWeb/releases "Named link title")

Read our Documentation [here](https://docs.prolifics.com)

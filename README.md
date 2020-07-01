# ParsingJSONUsingCFromPanther
This repository contain sample code on how to parse JSON data using C from Panther. In this Sample JSON data is sending from caller screen to servicescreen.jam screen which send the response back to first screen as a parsed JSON data with the help of C function.  

# Prerequisites
Panther Web 5.5*

# This repository consists of 4 files
* Panther screen name caller
* Panther screen name servicescreen.jam
* caller.html
* servicescreen.html


# Caller screen
Panther caller screen contains a Panther push button from which JavaScript function is executing at the on click property of push button. 

# Servicescreen screen
Panther servicescreen.jam screen contains two single line text fields and two multiline text fields. One MLT is used to get the JSON data from caller screen and Other MLT gets JSON parsed data from C function. In the JPL of this screen web_enter function is executing that call the C function that parse the JSON data.

# Caller.html
HTML template is attached to the Panther caller screen via property WEB OPTION->HTML OPTIONs->HTML Template. It consist of JavaScript functions that is calling from the on click property of push button. It also consist the function that makes a AJAX call to send JSON data to Panther servicescreen.jam screen. 

# Servicescreen.html
HTML template is attached to the Panther caller screen via property WEB OPTION->HTML OPTIONs->HTML Template. It consist of raw MLT property to get the response.


Need a Panther Web 552 Redhat Image? [Click Here](https://hub.docker.com/r/prolificspanther/pantherweb "Named link title") 

[Click Here](https://prolifics.com/panther-trial-license-request/ "Named link title") for a 45-day license.

How to set up a Panther Servlet Web Application? [Click Here](https://github.com/ProlificsPanther/PantherWeb/releases "Named link title")

Read our Documentation [here](https://docs.prolifics.com)

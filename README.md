# Unix-System-for-internal-and-external-commands-using-C-shell
A unix system to execute three specific commands for c shell:
1. **word (Internal command):**
    Reads the number of words (assume word is a “space-separated” string) in a text file, and throws an error if the file does not exist. 
    Syntax: word [-option] [file_name]
    Note: if no option is passed then there should be only one file, the number of files may vary as per option and the same would reflect in syntax .
    It should additionally also cater 2 options:
    -n : ignores new line character 
    -d : difference between the word sizes of two text files

2. **dir (external command):**
    It creates a directory, and then changes the path to that directory. It is an external command, throw an error if that directory already exists.
    Syntax: dir [-option] [dir_name]
    It should additionally also cater 2 options:
    -r : removes if the directory already exists and create a new directory instead of throwing an error  
    -v : print a message for each step in the running of this command

3. **date (external command):**
    It returns the last modified date and time of a particular file.  It is an external command
    Syntax: date [-option] [file_name]
    It should additionally also cater 2 options:
    -d : display time described by STRING 
    -R : output date and time in RFC 5322 format

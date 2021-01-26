Simple tools for handling massive text files
-----------------------

This repo was born out of bitter experience. On more than one occasion, I was analysing data from some big database and me and the database guy just could not speak the same language (I'm a statistician). I think this is quite common. I tried to explain what I needed and he thought I was an idiot. What you usually get given (grudgingly, because their boss said they had to do it) is one colossal "flat file". Sometimes these are too big to get into your RAM, sometimes too big for a particular piece of analysis software, and sometimes you just know it would make life a lot easier to split it into chunks and loop over them, or pull out just one line at a time to inspect them. So I ended up making some of these little C++ utilities, to handle the file straight off ROM without having to read the whole thing in, and to do so quickly.

Usually they got written for a specific job and have to be generalised before they can be shared, so they'll pop up here from time to time.

If you want a decent test case, look up Chris Whong's New York 2013 taxi data.

Utilities like this probably exist already in all sorts of forms, but I don't care, they're just sitting around and might be useful for someone.

They all use C++11's to_string, but you could work without that if you wanted to, it's just convenient.

Filesplitter
----------------------

Called like this:

    ./filesplitter what-a-massive-file.data 2000

this will crack apart what-a-massive-file.data (insert your own name, obviously) by rows, so you get a series of smaller files called split1, split2, and so on, each one being 2000 lines long. This would work well for files where one row is one entry/observation, and there is a separate dictionary. If the first row is column headers, like in a delimited text file such as CSV, then you want to use csvsplitter instead.

csvsplitter
----------------------

This is very similar to filesplitter, except that it repeats the first line in every file, and calls them split1.csv, split2.csv and so on. You can use it for any kind of delimiter, it doesn't look for commas.



Readaline
---------------------

Called like this:

    ./readaline myasciifile.txt 41318414

this will print the 41,318,414th line of myasciifile.txt on the screen.

or like this:

    ./readaline myasciifile.txt 41318414 100

prints 100 lines starting at the 41,318,414th line.

or you can get the line number included in the output:

    ./readaline myasciifile.txt 41318414 100 c

will show the line number followed by a comma and a space, then the contects of the line (in a CSV context, this inserts a new column on the left containing the row numbers from the original big file)

    ./readaline myasciifile.txt 41318414 100 l

gives you the row number, then a carriage return, then the contents

    ./readaline myasciifile.txt 41318414 100 b

doesn't show the line number but does put a blank line between the lines of the big file.    

That's it. Of course, you can pipe it into a new file, which is pretty handy.

As the lengths of lines are unpredictable, it has to start from the beginning and count lines, so the further into the file you are, the longer it will take. However, if you know the lengths are fixed throughout the file, try readaline-fixed (see below), which will be a LOT faster.

Readaline-starting
---------------------

Called like this:

    ./readaline-starting myasciifile.txt N41318414 N41318415

this will read through myasciifile.txt until it finds a line starting with N41318414, then prints that line and every line that follows until either the end of the file or it finds a line starting with N41318415. This is intended to help if your entries span multiple lines and are indexed uniquely in some way that you can predict (probably consecutive numbers, but that's not essential). Obviously, be careful with the third argument, the end search term, because if it doesn't find it, the entire file from the start line onward will get displayed (unless that's what you want).

You can also omit the third argument, which will show you just the single line beginning with the start search term (N41318414 in this case)

Readaline-fixed
---------------------

Yeah, I know. Maybe one day.

Readthoselines
----------------------

    ./readthoselines mybigfile.csv linenumbers.txt c

This expects linenumbers.txt to contain an integer on each line and nothing else; those integers *must* be sorted in ascending order! and those are the line numbers that get retrieved from mybigfile.csv. They print to *cout*, so you probably want to pipe them into a new file. The letter on the end (c, b, l) is the same option for showing line numbers as in readaline (see above). You do need to specify two file names, but the letter is optional.


Count-lines
---------------------

Guess what?

    ./count-lines mybigfile.txt

will tell you how many lines mybigfile.txt contains. I find one core of a 2015 MacBook Pro counts about 10 million lines a minute this way.

Some ideas for use
---------------------

**Random sampling:** Use count-lines over a set of big files to find out how many lines are in each. Make your (weighted or stratified) random sample of lines from these (it's easy in R or whatever, not worth incorporating into C++), then feed that list of lines back through readthoselines

Some ideas to work on
----------------------

Generate a CSV file which acts as an index of the byte position of every nth line, so that other programs can go to a given line number more quickly using fseek.

Simple tools for handling massive text files
-----------------------

This repo was born out of bitter experience. On more than one occasion, I was analysing data from some big database and me and the database guy just could not speak the same language (I'm a statistician). I think this is quite common. I tried to explain what I needed and he thought I was an idiot. What you usually get given (grudgingly, because their boss said they had to do it) is one colossal "flat file". Sometimes these are too big to get into your RAM, sometimes too big for a particular piece of analysis software, and sometimes you just know it would make life a lot easier to split it into chunks and loop over them, or pull out just one line at a time to inspect them. So I ended up making some of these little C++ utilities, to handle the file straight off ROM without having to read the whole thing in, and to do so quickly.

Usually they got written for a specific job and have to be generalised before they can be shared, so they'll pop up here from time to time.

Utilities like this probably exist already in all sorts of forms, but I don't care, they're just sitting around and might be useful for someone.

Filesplitter
----------------------

Called like this:

    ./filesplitter what-a-massive-file.csv 2000

this will crack apart what-a-massive-file.csv (insert your own name, obviously) by rows, so you get a series of smaller files called split1.csv, split2.csv, and so on, each one being 2000 lines long. I'm often dealing with CSV files in this context but you could easily change the name that comes out to whatever suits you.

If you want a decent test case, look up Chris Whong's New York 2013 taxi data.

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

    ./filesplitter what-a-massive-file.csv 2000

this will crack apart what-a-massive-file.csv (insert your own name, obviously) by rows, so you get a series of smaller files called split1.csv, split2.csv, and so on, each one being 2000 lines long. I'm often dealing with CSV files in this context but you could easily change the name that comes out to whatever suits you.

Readaline
---------------------

Called like this:

    ./readaline myasciifile.txt 41318414

this will print the 41,318,414th line of myasciifile.txt on the screen. That's it. As the lengths of lines are unpredictable, it has to start from the beginning and count lines, so the further into the file you are, the longer it will take. However, if you know the lengths are fixed throughout the file, try readaline-fixed (see below), which will be a LOT faster.

Readaline-starting
---------------------

Called like this:

    ./readaline-starting myasciifile.txt N41318414 N41318415

this will read through myasciifile.txt until it finds a line starting with N41318414, then prints that line and every line that follows until either the end of the file or it finds a line starting with N41318415. This is intended to help if your entries span multiple lines and are indexed uniquely in some way that you can predict (probably consecutive numbers, but that's not essential). Obviously, be careful with the third argument, the end search term, because if it doesn't find it, the entire file from the start line onward will get displayed.

You can also omit the third argument, which will show you just the single line beginning with the start search term (N41318414 in this case)

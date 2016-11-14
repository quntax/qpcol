# List of spotted/reported issues or bugs

* QPcol dirscanning and hashing routines are little buggy. When video with hash X
  is already in DB (active, not blacklisted), and the same file is scanned before original file, videoID pointer
  is moved to new file position, and old one becomes an orphan. Pointer should stay
  at original file (if file exists, has has, is not blacklisted, then: leave it as is!)
* Somehow videos from the same URL are registered twice. Hash computing?
* Very bad db conn and transactiosn handling across qpcol and xget - they lock eachself and cause data loss in some cases. FIX IT.
  Perform audit of models, modelhandlers, types. DO THE SAME FOR XGET!!!
* Playlist mode does not update original URLs
* Open regular file by mediawidgets
* Moving file does not move *.url/*.xgeturl files, if present.
* DOwnloading list of files is messy. Problem with generating output filenames. It occurs also when getting 2 different videos, but having
  the same name (title)
* Webview works again, for 2 sites for now. Yet application crashes on second searh, probably null ptr call
* DB Initialization and remove qpcol_init_db script from bin
* video model refresh does not keep current position on videos list, soring is also lost
* UTF8 support, especially for tag names
* videos view - add time in UTC, not localzone
* tag editor when playing movie - see mainwindow.cpp:382 comment
* check downloaders/extractors
* Search & remove dead dead entries in database (xget)
* xflogger.com
* Downloads list: store in database (db model is ready)
* Clipboard monitor: add files to queue instead of instand download (option, switchable) // i think it's done
* Download manager (resuming, displaying links, etc)
* DATABASE setup (reader for backup, writer for new one) // backup bash script and qpcol acition implemented)
* check hash of every video, if it exists in database (on web search)
* switching providers w key
* probably: isearchplugin interface redesign needed, according to this:
void Youjizz::parseResult()
{
    result = webPage->mainFrame()->findAllElements("div#main span#miniatura");
    /*
     TODO: make only this method virtual, remove parseElement.
     All logic should be done here. parseResult() would be called at the end of
    loadFinished slot, where QQueue<QWebElement> would be elements to emit().
    It would act as a buffer of processed/not sent elements
    */
/*
    foreach(QWebElement element, result) {
        qDebug() << element.toPlainText();
    }*/
}
* extract videos on demand, by default load page url instead of video url
* crashing on video select (probably mediawidget)
* downloads database (save links, for resume support)

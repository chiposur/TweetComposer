# TweetComposer
 A native desktop application for working with tweet drafts and reusable tweet templates.

Key features include:
* Creating, editing and deleting drafts and templates on disk
* Searching for drafts and templates by name or text
* Creating bold and italic Math sans and Math serif tweets using the tweet editor
* Exporting and importing drafts and templates through JSON files
* Posting tweets to Twitter via the TwitterApiClient using TLS 1.3 for speed and security

# Build
 C++:	17<br/>
 Qt:	5.15.2<br/>
 OpenSSL:	1.1.1<br/>
 Compiler: MSVC 16.8.30804.86<br/>
 
 Qt's network module relies on OpenSSL for handling encrypted connections such as TLS, and with Qt release 5.12.4 support was added for TLS 1.3 by upgrading to version 1.1.1 of OpenSSL. In order to use the latest TLS standard Qt 5.12.4 or greater is required.

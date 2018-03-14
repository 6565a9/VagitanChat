# VagitanChat
- Protocol for chatting.
- Idea: Create server with own protocol and support of IRC protocol.
- [x] NativeProtocol(beta)
- [ ] IRCProtocol
## Protocol
```
 :USER %Username% %Password% 
   Correct answer: :WELCOME %Username%
   Errors: ":ERROR not enought params/:ERROR much params", ":ERROR not registered", ":ERROR uncorrect password"
   
   EXAMPLE:
   Client-> :USER Client Pass
   Server<- :WELCOME Client

```

```
  :REGISTER %Username% %Password%
  Correct answer: ":REGISTERED"
  Errors: ":ERROR Registered", ":ERROR not enought params/:ERROR much params"

  EXAMPLE:
  Client-> :REGISTER Client Pass
  Server<- :REGISTERED
```

```
  :PRIVMSG @%chatName% %text%
  Correct answer: ":PRIVMSG @%chatName% %ownUsername% %text%"
  ERRORS: ":ERROR NOT FOUND ROOM @%chatName%"
  
  :PRIVMSG %username% %text%
  Correct answer: no answering.
  ERRORS: ":ERROR NOT FOUND"
EXAMPLE:
  Client-> :JOIN SomeChat
  Server<- :ROOM SomeChat CREATED
  Server<- :ADDED Client SomeChat
  Client-> :PRIVMSG @SomeChat hello!
  Server<- :PRIVMSG @SomeChat Client hello!
...
1 Client
Client-> :USER Client Pass
Server<- :WELCOME Client
Client-> :PRIVMSG Login message to client
Server<- :PRIVMSG Login message to Login

2 Client
Client-> :USER Login Password
Server<- :WELCOME Login
Server<- :PRIVMSG Client message to client
Client-> :PRIVMSG Client message to Login
~
1 Client
Client->:USER Client Pass
Server<-:WELCOME Client
Client->:JOIN RUM
Server<-:ROOM RUM CREATED
Server<-:ADDED Client RUM
Server<-:ADDED Test RUM
Server<-:PRIVMSG @RUM Test all hi
Client->:PRIVMSG @RUM Hi there
Server<-:PRIVMSG @RUM Client Hi there
Client->:QUIT quiting
Server<-:REMOVED Client RUM

2 Client
Client->:USER Test Test
Server<-:WELCOME Test
Client->:JOIN RUM
Server<-:ADDED Test RUM
Client->:PRIVMSG @RUM all hi
Server<-:PRIVMSG @RUM Test all hi
Server<-:PRIVMSG @RUM Client Hi there
Server<-:REMOVED Client RUM
Server<-:QUIT @RUM  LEAVING
...

```

```
:JOIN %chanName%
Correct answer ":ROOM %chanName% CREATED", ":ADDED %ownUsername% %chanName%" -> for added to room
ERRORS: ":ERROR ALREADY ADDED"
```

```
:LEAVE %RoomName%
Correct answer: ":REMOVED %OwnUsername% %RoomName%"
ERRORS: ":ERROR undefined room"

EXAMPLE:
Client-> :USER Login Password
Server<- :WELCOME Login
Client-> :JOIN room
Server<- :ROOM room CREATED
Server<- :ADDED Login room
Client-> :LEAVE room
Server<- :REMOVED Login room


```

```
:PING %anytext%

EXAMPLE:
Client-> :PING .
Server<- :WRITEANYATEXT 
Client->anytext
Server<-anytext
```

```
:QUIT %anytext%
Correct answ: no. closing connection.
```

```
:LIST %channame%
Correct: ":LIST sekta %listofusers%"
ERRORS: ":ERROR ROOM NOT FOUND"

EXAMPLE:
Client->:USER Client Pass
Server<-:WELCOME Client
Client->:JOIN test
Server<-:ROOM test CREATED
Server<-:ADDED Client test
Server<-:ADDED Login test
Client->:LIST test
Server<-:LIST test Client Login 

```

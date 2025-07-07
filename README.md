# Social Network Simulation in C++

This project implements a simulation of a social networking system, written in C++. Users can register, log in, manage friendships, post and reply to messages, and interact with each other through a basic console interface and text-based file storage.

## 🚀 Features

- **User Registration**  
  New users can register with a name or email and a password. Information is stored in `database.txt`.

- **User Login / Logout**  
  Registered users can log in to access their personal menus and log out at any time.

- **Personal Wall View**  
  Users can view their own wall which includes:
  - Their posts
  - Posts from friends
  - Replies and discussions

- **Friend's Wall Access**  
  Users can:
  - Leave a message on a friend’s wall
  - Reply to specific posts
  - Like friend posts  
  Data is stored in text files (`Post.txt`, `Reply_to_post.txt`, `Likes.txt`).

- **Friend Requests**
  - Send a friend request to any registered user who is not already a friend.
  - Requests are stored in a `Requests` section.

- **Accept or Reject Requests**  
  Accepting a request adds both users to each other's friend files.

- **Delete Friends**  
  Users can remove one or more friends using the `deletefriends()` function, which removes mutual friendship from both files.

- **Friend List View**  
  Users can view a list of their current friends.

- **Navigation and Session Control**  
  - Return to main menu
  - Log out
  - Exit the program after logout

## 💾 Data Storage

All user data and actions are stored in plain text files:
- `database.txt`: Stores registered users and their password
- `<username>.txt`: Stores friends of each user
- `Post.txt`: Contains user posts
- `Reply_to_post.txt`: Contains post replies
- `Likes.txt`: Tracks likes per post

## 🛠️ Technologies Used

- **Language:** C++
- **File Handling:** Text file I/O
- **Core Concepts:** Structs, Menus, User Input, Basic Authentication, File-based Storage

## 📦 Compilation

To compile and run the project:

g++ social_network.cpp -o social_network

./social_network

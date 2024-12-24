## 🌐 What is a (Matt) Daemon?

A **daemon** is a background process that operates independently of user interaction. Originating from MIT in the 1960s, the term reflects an automated helper that handles tasks such as logging, system monitoring, and managing network connections. On Windows systems, similar programs are called "services."

With this project, you'll step into the shoes of a systems programmer to build your own daemon.

---

## 🛠️ Key Features

### 🔑 Core Functionality
1. **Daemon Behavior**:
    - Runs in the background like a true UNIX daemon.
    - Operates exclusively with root privileges.

2. **Networking**:
    - Listens on port `4242` for incoming connections.
    - Handles up to **3 simultaneous clients**.

3. **Message Handling**:
    - Accepts and logs all incoming messages.
    - Shuts down gracefully upon receiving the command `quit`.

4. **Logging**:
    - Logs all actions with timestamps in the format `[ DD / MM / YYYY - HH : MM : SS ]`.
    - Log files are stored in `/var/log/matt_daemon/matt_daemon.log`.

5. **Lock Mechanism**:
    - Ensures only one instance of the daemon runs by creating a lock file at `/var/lock/matt_daemon.lock`.
    - Deletes the lock file upon shutdown to maintain system integrity.

6. **Signal Handling**:
    - Captures system signals and logs them appropriately.
    - Shuts down cleanly when required.

---

## 📋 Usage Instructions

1. **Build the Project**:
    - Use the provided `Makefile` to compile the daemon:
      ```bash
      make
      ```

2. **Run the Daemon**:
    - Start the daemon as root:
      ```bash
      sudo ./Matt_daemon
      ```

3. **Interact via a Client**:
    - Connect using tools like `netcat`:
      ```bash
      nc localhost 4242
      ```
    - Send messages to the daemon. For example:
      ```plaintext
      Hello World
      quit
      ```

4. **View Logs**:
    - Check the log file for details:
      ```bash
      tail -f /var/log/matt_daemon/matt_daemon.log
      ```

---


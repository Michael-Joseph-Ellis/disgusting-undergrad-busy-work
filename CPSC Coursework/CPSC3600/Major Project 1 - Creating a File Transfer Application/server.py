# server.py

from socket import *
from struct import pack, unpack
import os, hashlib, sys, logging, math


class FileTransferServer:
    def __init__(self, port, recv_length):
        """
        Initialize a new FileTransferServer instance.

        This constructor sets up logging for the server, creates a directory to store 
        received files, and stores the provided network parameters for use when listening
        for client connections.

        Args:
            port (int): The port number on which to listen for client connections.
            recv_length (int): The maximum size in bytes of data to request from a client
                socket in a single recv call.

       Note:
            The logging setup should not be modified, as it is configured to provide useful 
            debugging output to students working on this project.
            
            The recv_length parameter puts a limit on the maximum chunk size that can be 
            used during file transfers. Make sure your server will never request more than recv_length
            bytes from a client socket at a time.
        """

        # Do not modify this logger code. You can continue to use print() commands for your code.
        # The logger is in place to ensure that you receive proper output and debugging messages from the tester
        self.logger = logging.getLogger("SERVER")
        self.handler = logging.StreamHandler(sys.stdout)
        formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
        self.handler.setFormatter(formatter)
        self.logger.addHandler(self.handler)
        self.logger.propagate = False
        self.logger.info("Initializing server...")
        # End of logger code

        # Create a directory to store received files
        if not os.path.exists("received_files"):
            os.makedirs("received_files")

        self.port = port
        self.recv_length = recv_length
        self.server_socket = None
        self.is_running = True


    def start(self):
        """
        Start the server listening for client connections.

        This method creates a TCP socket, binds it to the host and port specified during
        server initialization, and begins listening for incoming client connections.         
        
        IMPORTANT
        - The method should also configures the server socket with a timeout of 1 second.
        - Do NOT attempt to accept a connection or receive any messages from the client in 
            this function. That will be done in the run() function.

        Returns:
            bool: True if the server was started successfully, False otherwise.
        
        Exceptions:
            - OSError: Indicates a problem with socket creation, binding, or listening, which
            is logged for debugging purposes.

        Usage Example:
            server = FileTransferServer(port=12345)
            if server.start():
                server.run()
        """
        # TODO: Implement the functionality described in this function's docstring

        try:
            self.server_socket = socket(AF_INET, SOCK_STREAM)
            self.server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            self.server_socket.bind(('', self.port))
            self.server_socket.listen(1)
            self.server_socket.settimeout(1.0)  # 1 second timeout
            self.logger.info(f"Server listening on port {self.port}")
            return True
        except OSError as e:
            self.logger.error(f"Failed to start server: {e}")
            return False

    def write_file(self, filename, data):
        """
        Save the provided file data using the specified filename.

        This is a helper function that saves the provided bytes to a file in a directory
        named "received_files" in the current working directory.

        Args:
            filename (str): The name to use when saving the file.
            data (bytes): The raw bytes of the file to be saved.

        Note:
            This helper function is provided for use when implementing the run method.
            It should not be modified by students.
        This is a helper function that saves the provided bytes to a file in a directory
        named "received_files" in the current working directory.

        Args:
            filename (str): The name to use when saving the file.
            data (bytes): The raw bytes of the file to be saved.

        Note: 
            This helper function is provided for use when implementing the run method.
            It should not be modified by students.
        """
        with open(os.path.join("received_files", filename), "wb") as file:
            file.write(data)


    def run(self):
        """
        Run the server, accepting client connections and handling file transfer requests.

        This method implements the core functionality of the server. It runs in an infinite 
        loop, waiting for client connections. It only handles a single client connection at a time.
        
        Once a connection has been established, begin listening for file transfer request messages from the 
        currently connected client. When you receive a message, send an ACK message with a chunk_number of 0 
        (i.e. the first chunk needed) and then begin receiving the file. Once a file has been received write 
        it to disk using self.write_file() and  begin listening for another file transfer request from the same 
        client. If the client disconnects, attempt to accept a new connection from another client.
        
        Given the pattern where we 1) attempt to accept a connection from a new client, and then 2) attempt to 
        receive multiple files from a single client, you will need to use two nested while loops. Set each of these
        while loops to continue so long as self.is_running is True.

        Exceptions:
            - TimeoutError: Occurs when accepting a connection times out. This is an EXPECTED exception and 
                            does not indicate a problem has occurred. Simply continue code execution when 
                            handling this exception. 
            - OSError: Indicates an issue with handling the socket connection, logged for debugging.
            - Exception: Catches and logs any unforeseen errors to avoid crashing the server.

        Usage Example:
            server = FileTransferServer(5000)
            if server.start():
                server.run()

        Note:
            This method is blocking; it will continuously run until the server is explicitly
              shutdown with the shutdown() method. We add a timeout to the server socket in order
              to ensure that we don't get stuck blocking and never see that is_running has been 
              changed to false.
        """
        # TODO: Implement the functionality described in this function's docstring
        while self.is_running:
            try:
                print("[DEBUG] Waiting for a client connection...")
                conn, addr = self.server_socket.accept()
                print(f"[DEBUG] Accepted connection from {addr}")

                while self.is_running:
                    # Step 1: receive file transfer request
                    request = conn.recv(self.recv_length)
                    if not request:
                        break

                    filename, file_size, chunk_size, checksum_length = self.unpack_transfer_request_message(request)
                    print(f"[DEBUG] Preparing to receive file: {filename}, {file_size} bytes")

                    # Step 2: send initial ACK (expecting chunk 0)
                    ack = self.pack_ack_message(0)
                    conn.sendall(ack)

                    # Step 3: receive the file
                    file_data = self.receive_file(conn, file_size, chunk_size, checksum_length)
                    if file_data:
                        self.write_file(filename, file_data)
                        print(f"[DEBUG] File '{filename}' received and saved.")
                    else:
                        print("[DEBUG] File transfer failed or was incomplete.")

            except TimeoutError:
                continue
            except Exception as e:
                print(f"[DEBUG] Server error: {e}")


    def receive_file(self, conn, file_size, chunk_size, checksum_length):
        """
        Receive a file from a client connection, chunk by chunk.

        This method implements the server-side logic for receiving a file from a connected
        client. The client's socket is passed in as a parameter so we can talk to the client. On starting to 
        receive the file, repeatedly call self.receive_chunk() to receive each chunk from the client and then 
        send an ACK message requesting the next chunk. Return the received filedata once it has all been received.
        
        Be careful to never request more data than is actually remaining to be transfered. So long as the amount 
        of remaining data is larger than the chunk size, request an amount of data equal to the chunk size. 
        However, the final chunk will almost certainly be smaller than the chunk size. In this case be careful 
        to request exactly how much data still needs to be transfered.
        
        You will need to handle if a client disconnects while attempting to receive a chunk. Since you're not 
        actually reading from a socket in this function you will have to detect this in self.receive_chunk() and 
        then use whatever values are returned by that function to determine the client has disconnected and how 
        to proceed from there (i.e. pass that information back up to run() where this function was called).

        Args:
            conn (socket): The socket representing the client connection.
            file_size (int): The total size of the file being received.
            chunk_size (int): The size of each chunk of the file to be received.
            checksum_length (int): The length in bytes of the checksum hash used.
        
        Returns:
            bytes: The complete file data received from the client, or None if the transfer
                fails or the client disconnects.

        Useage Example:
            file = self.receive_file(conn, file_size, chunk_size, checksum_length)
        """
        # TODO: Implement the functionality described in this function's docstring
        file_data = bytearray()
        expected_chunk = 0

        while expected_chunk * chunk_size < file_size:
            amount_to_receive = min(chunk_size + 4 + checksum_length,  # 4 = chunk number
                                    file_size - expected_chunk * chunk_size + 4 + checksum_length)

            chunk_number, chunk_bytes = self.receive_chunk(conn, amount_to_receive, checksum_length)

            if chunk_number == -1:
                self.logger.warning("Client disconnected during transfer.")
                return None

            if chunk_bytes is not None:
                file_data.extend(chunk_bytes)
                expected_chunk += 1
            # Send ACK either way
            ack = self.pack_ack_message(expected_chunk)
            conn.sendall(ack)

        return bytes(file_data)


    def receive_chunk(self, conn, chunk_size, checksum_length):
        """
        Receive a single chunk of a file from a connected client.

        Attempts to receive a chunk of the file. Remember the format used for sending a chunk, which includes:
        * the chunk number (int)
        * the content of the chunk
        * a checksum based on the chunk number and the content of the chunk
        Make sure you correctly receive all of this information and don't accidently treat the chunk number as 
        part of the chunk data, or vice versa.

        You will not be able to read all of the chunk data at once, due to the chunk size being larger than 
        self.recv_length, the maximum amount of data you are allowed to request from a socket in this program. 
        As such, you will need to recv data and buffer it until you've received the entire chunk. Make sure you
        do not attempt to read more data than is actually remaining in the chunk; the final piece of the chunk 
        may be smaller than self.recv_length, in which case you must detect this and request the appropriate 
        smaller value.

        Once you have received the chunk number and the content of the chunk, make sure you also receive the 
        checksum. Compare the received checksum against a checksum you generate based on the chunk number and
        chunk data you have received. If the checksums match, request the next chunk. If they do not match, 
        request that this chunk be sent again. You can either send that ACK inside of this function, or inside of
        receive_file() upon this function returning.

        Make sure that you don't return bad data in the event that the checksums don't match. In this case make 
        sure you don't use the chunk data you've received as it isn't trustworthy.

        If you detect that the client has disconnected which receiving a chunk, make sure you inform the 
        receive_file() function of this when you return (how you do so is up to you).

        Args:
            conn (socket): The socket representing the client connection.
            chunk_size (int): The size of the chunk to receive.
            checksum_length (int): The length in bytes of the checksum hash used.

        Returns:
            tuple: A tuple (chunk_number, chunk_data), where:
                chunk_number (int): The sequence number of the received chunk, incremented by 1
                    if the chunk was received successfully, or the received sequence number if
                    the checksum does not match. If the client disconnects, this is -1.
                chunk_data (bytes): The raw bytes of the received chunk data, or None if the 
                    chunk was not received successfully or the client disconnected.

        Useage Example:
            next_chunk_number, data = self.receive_chunk(conn, amount_of_data_to_recv, checksum_length)
        """
        # TODO: Implement the functionality described in this function's docstring
        buffer = bytearray()
        try:
            while len(buffer) < chunk_size:
                recv_size = min(self.recv_length, chunk_size - len(buffer))
                part = conn.recv(recv_size)
                if not part:
                    return -1, None
                buffer.extend(part)

            chunk_number = unpack('!I', buffer[:4])[0]
            chunk_data = buffer[4:-checksum_length]
            received_checksum = buffer[-checksum_length:]

            computed_checksum = self.compute_hash(buffer[: -checksum_length], checksum_length)

            if computed_checksum == received_checksum:
                return chunk_number, chunk_data
            else:
                # Return same chunk number to request resend
                return chunk_number, None

        except:
            return -1, None
        

    def unpack_transfer_request_message(self, bytes):
        """
        Unpack a client transfer request message into its component fields.
        
        A transfer request message consists of the following fields:
        - Filename length (unsigned short)
        - Filename (string of variable length) 
        - File size in bytes (unsigned int)
        - Chunk size in bytes (unsigned short) 
        - Checksum length in bytes (unsigned char)

        Since you don't know how long the filename is you'll want to first unpack the filename_length
        field and then use that to unpack the rest of the message.

        Args:
            bytes (bytes): The packed binary transfer request message from the client.
        
        Returns:
            tuple: A tuple (filename, file_size, chunk_size, checksum_length), where:
                - filename (str): The name of the file being transferred.
                - file_size (int): The total size of the file in bytes.
                - chunk_size (int): The size of each chunk of the file to be sent.
                - checksum_length (int): The length in bytes of the checksum hash used.

        Useage Example:
            filename, file_size, chunk_size, checksum_length = self.unpack_transfer_request_message(data)
        """
        # TODO: Implement the functionality described in this function's docstring
        filename_length = unpack('!H', bytes[:2])[0]
        format_str = f'!H{filename_length}sIHB'
        unpacked = unpack(format_str, bytes[:2 + filename_length + 7])
        filename = unpacked[1].decode()
        file_size = unpacked[2]
        chunk_size = unpacked[3]
        checksum_length = unpacked[4]
        return filename, file_size, chunk_size, checksum_length
    

    def pack_ack_message(self, next_chunk_number):
        """
        Generate the packed binary data for a server acknowledgement message.

        A server acknowledgement message consists of the following fields:
        - ACK type (unsigned char), where 0 indicates a normal ACK  
        - Next expected chunk number (unsigned int)

        Args:
            next_chunk_number (int): The sequence number of the next expected chunk.
            
        Returns:
            bytes: The packed binary representation of the acknowledgement message.

        Useage Example:
            ack_msg = self.pack_ack_message(next_chunk_number)
        """
        # TODO: Implement the functionality described in this function's docstring
        return pack('!BI', 0, next_chunk_number)


    def compute_hash(self, data, hash_length):
        """
        Generates a hash of the provided data using the SHAKE-128 algorithm.

        In this assignment, we'll use the hashlib library to compute a hash of the data
        being shared between the client and the server. A hash is a fixed-length string
        generated based on arbitrary input data. The same data will result in the same
        hash, and any change to the data will result in a different hash.  We're using this 
        very simplistically to introduce the idea of hashing and integrity checking, which 
        we'll be exploring in more detail later in the semester.

        1. Import hashlib and call hashlib.shake_128() to create a new SHAKE-128 hash object.
        2. Use the update() method to add the data to the hash object.
        3. Use the digest() method to retrieve the hash value and return it.

        The shake_128 algorithm is convenient for us since we can specify the length of the
        hash it produces. This allows us to generate a short hash for use in our tests.
        
        Parameters:
            - data (bytes): Data for which the hash will be computed.
            - hash_length (int): Specifies the desired length of the hash output in bytes.

        Returns:
            - bytes: The computed hash of the data, which can be used for integrity checks.

        Note:
            - This method is used within the file transfer process to ensure the integrity
            of received data by comparing the computed hash with one provided by the client.
        """
        # TODO: Implement the functionality described in this function's docstring
        hash_obj = hashlib.shake_128()
        hash_obj.update(data)
        return hash_obj.digest(hash_length)


    def shutdown(self):
        """
        Shuts down the server by stopping its operation and closing the socket.

        This method safely terminates the server's operation. It stops the server from
        running, removes the logger handler, and closes the server socket if it is open.

        The method logs the shutdown process, providing visibility into the client's
        state transitions. It's designed to be safely callable even if the socket is
        already closed or not initialized, preventing any unexpected exceptions during
        the shutdown process.

        Usage Example:
            server.shutdown()

        Note:
            - Call this method to cleanly shut down the server after use or in case of an error.            
            - Do NOT set server_socket to None in this method. The autograder will examine
                server_socket to ensure it is closed properly.
        """
        self.logger.info('Server is shutting down...')

        # TODO: Implement the functionality described in this function's docstring
        self.is_running = False 
        if self.server_socket:
            try:
                self.server_socket.close()
                self.logger.info("Server socket closed.")
            except OSError as e:
                self.logger.error(f"Error while closing server socket: {e}")
        self.logger.removeHandler(self.handler)


if __name__ == "__main__":
    server = FileTransferServer(5000, 1024)
    if server.start():
        print("Server started successfully.") # This print statement is for testing purposes.
        server.run()
    else: 
        print("Failed to start server.") # This print statement is for testing purposes.
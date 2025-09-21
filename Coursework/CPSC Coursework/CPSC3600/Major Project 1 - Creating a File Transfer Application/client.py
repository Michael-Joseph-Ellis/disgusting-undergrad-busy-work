from socket import *
from struct import pack, unpack
import os, time, sys, logging, hashlib, math

"""
Protocol Description
1. Client initiates connection with the server
2. Client sends a request to the server to transfer a file. This request includes
    * the name of the file
    * the size of the file
    * the chunk size to be used during transfer
    * the checksum length used to validate the file chunks
3. Server responds with an ACK indicating it is ready to receive the file. The ACK uses the following format
    * ACK type
    * the next expected chunk number. This should be zero here as the server needs the first chunk
4. The client begins sending chunks of the file to the server. Chunks use the following format
    * the chunk number
    * the current file chunk
    * a checksum of the other data in this chunk
5. The server receives chunks and sends an ACK message. The ACK uses the following format:
    * ACK type
    * the next expected chunk number. Note: if the packet is received successfully, this is the next packet number. If the packet was NOT received successfully (i.e. the checksum didn't validate) then this should be the previously expected chunk number
6. This continues until the entire file has been received and the server saves the file and sends a final ACK to the client. The client can then either send another file, or close the connection and quit.

"""

class FileTransferClient:
    def __init__(self, host, port, chunk_size=32768, hash_length=8):
        """
        Initializes the FileTransferClient.

        This constructor sets up the logging configuration for the client and stores and provided parameters.

        Parameters:
            host (string): the hostname or IP address to connect to
            port (int): The port number to connect TODO - 
            chunk_size (int): the number of bytes in each chunk to use when transmitting the file
            hash_length (int): the length of the hash in bytes

        Note:
            The logger setup provided should not be modified and is used for outputting 
            status and debugging messages.
        """
         
        # Do not modify this logger code. You can continue to use print() commands for your code.
        # The logger is in place to ensure that you receive proper output and debugging messages from the tester
        self.logger = logging.getLogger("CLIENT")
        self.handler = logging.StreamHandler(sys.stdout)
        formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
        self.handler.setFormatter(formatter)
        self.logger.addHandler(self.handler)
        self.logger.propagate = False
        self.logger.info("Initializing client...")
        # End of logger code

        self.host = host
        self.port = port
        self.chunk_size = chunk_size
        self.hash_length = hash_length

        self.client_socket = None

    def start(self):
        """
        Initiates a connection to the server and marks the client as running. This function
        does not attempt to send or receive any messages to or from the server.

        This method is responsible for establishing a socket connection to the specified
        server using the host and port attributes set during the client's initialization.
        It creates a TCP socket object and attempts to connect to the server. It logs
        the connection attempt and reports any errors encountered during the process.

        Returns: 
            True or False depending on whether the connection was successful.

        Exceptions:
            - OSError: Raised if the socket encounters a problem (e.g., network
              issue, invalid host/port).

        Usage Example:
            client = FileTransferClient(host='192.168.1.10', port=12345, hash_length=8)
            if client.start():
                ... do something ...

        Note:
            - It is important to call this method before attempting to send or receive
              messages using the client.
            - Ensure that the server is up and running at the specified host and port
              before calling this method.
        """
        # TODO: Implement the functionality described in this function's docstring
        
        try:
            print("[DEBUG] Attempting to connect to server...")
            self.client_socket = socket(AF_INET, SOCK_STREAM)
            self.client_socket.connect((self.host, self.port))
            print(f"[DEBUG] Connected to server at {self.host}:{self.port}")
            return True
        except OSError as e:
            print(f"[DEBUG] Connection error: {e}")
            return False


    def read_file(self, filepath):
        """
        Reads the contents of a file and returns the data as a byte object.

        This is a helper function. You do not need to modify it. You can use it in the send_file
        method to read the contents of a file and return the data as a byte object.
        """
        with open(filepath, "rb") as file:
            data = file.read()
            return data
        

    def send_file(self, filepath):
        """
        Sends a file to the server using the established connection.

        File Transfer Protocol:
        1.  Send a file transfer request to the server. Generate this request using the
            pack_transfer_request_message function
        2.  Receive a response from the server indicating that it is ready to start receiving 
            the file. Process this request using the unpack_ack_message function.
        3.  Repeat until the file is transfered successfully:
            a.  Send the file chunk specified in the previously received ACK message. Pack the
                chunk into the required format using the pack_file_chunk function.
            b.  Listen for an ACK from the server. Unpack it using the unpack_ack_message 
                function and extract the next chunk requested by the server.
        4.  End this process once the server asks for a chunk that is larger than the final 
            chunk of the file, as this indicates that the entire file has been received.

        Parameters:
            filepath (str): The path to the file to be sent.

        Returns:
            bool: True if the file was sent successfully, False otherwise.
        
        Exceptions:
            - TimeoutError: Raised if the socket times out while waiting for a response.
            - ConnectionResetError: Raised if the server resets the connection.
            - ConnectionAbortedError: Raised if the server aborts the connection.
            - OSError: Raised if the socket encounters a problem (e.g., network
              issue, invalid host/port).
              
        Usage Example:
            client = FileTransferClient("localhost", 5000)
            if client.start():
                client.send_file("source/test1.jpg")
        """
        # TODO: Implement the functionality described in this function's docstring
        try: 
            file_data = self.read_file(filepath)
            file_size = len(file_data)
            filename = os.path.basename(filepath)
            
            # Step 1: Send the transfer request message 
            request = self.pack_transfer_request_message(
                filename, 
                file_size, 
                self.chunk_size,
                self.hash_length
            )
            
            self.client_socket.sendall(request)
            
            # Step 2: Recieve ACK 
            ack = self.client_socket.recv(5) # 1B type + 4B chunk number
            ack_type, next_chunk = self.unpack_ack_message(ack)
            
            # Step 3: Send file chunks until the entire file is sent 
            while next_chunk * self.chunk_size < file_size: 
                start = next_chunk * self.chunk_size 
                end = min(start + self.chunk_size, file_size)
                chunk_bytes = file_data[start:end]
                
                chunk_packet = self.pack_file_chunk(next_chunk, chunk_bytes)
                self.client_socket.sendall(chunk_packet)
                
                ack = self.client_socket.recv(5) # 1B type + 4B chunk number
                ack_type, next_chunk = self.unpack_ack_message(ack)
                
            return True 
        
        except Exception as e:
            print(f"[DEBUG] Error while sending file: {e}")
            return False                
                    
    
    def pack_transfer_request_message(self, filename, file_size, chunk_size, checksum_length):
        """
        Generates the byte data for a transfer request message. This message should use 
        the following format:
        * filename_length [unsigned half]
        * filename [variable length byte string]
        * file_size [unsigned int]
        * chunk_size [unsigned half]
        * checksum_length [unsigned byte]

        Parameters:
            filename (str): The name of the file to be sent
            file_size (int): The size of the file to be sent, in bytes
            chunk_size (int): The size of each chunk to be used when transfering the file, in bytes
            checksum_length (int): the length of the checksum to be used

        Returns:
            bytes: the packed representation of the message defined above

        Useage Example:
            transfer_message = self.pack_transfer_request_message('myfile.jpg',304245, 8096, 16)
        """
        # TODO: Implement the functionality described in this function's docstring
        filename_bytes = filename.encode()
        filename_length = len(filename_bytes)
        
        return pack( 
                    f'!H{filename_length}sIHB', 
                    filename_length,
                    filename_bytes,
                    file_size,
                    chunk_size,
                    checksum_length
                    )


    def pack_file_chunk(self, chunk_number, chunk_bytes):
        """
        Generates the byte data for a file chunk message. This message should use the following format:
        * chunk_number [unsigned int]
        * chunk_bytes [bytes]
        * checksum [bytes]

        The checksum can be computed using the compute_hash function that you will implement below. 
        This file accepts bytes and generates a fixed length hash based on those bytes. To create the 
        checksum you will first need to pack the chunk number and the chunk bytes. You can then send 
        those bytes to the compute_hash function and concatenate the returned checksum to the bytes 
        you had previously packed.

        E.g. 
            bytes = pack(..., chunk_number, chunk_bytes)
            checksum = self.compute_hash(bytes)
            bytes = bytes + checksum

        Parameters:
            chunk_number (int): The number of this chunk
            file_bytes (bytes): The bytes contained in this chunk of the file
            checksum (bytes): The checksum computed based on the byte representation of the rest of this message

        Returns:
            bytes: the packed representation of the message defined above

        Useage Example:
            chunk = self.pack_file_chunk(3, data[3*self.chunk_size:4*self.chunk_size])
        """
        # TODO: Implement the functionality described in this function's docstring
        chunk_header = pack('!I', chunk_number) + chunk_bytes 
        checksum = self.compute_hash(chunk_header)
        return chunk_header + checksum


    def unpack_ack_message(self, bytes):
        """
        Unpack an ack message from the server. The ACK message from the server uses the following format:
        * ACK_type [unsigned byte] - a 0 indicates that everything is normal. We don't really use this 
          field in this protocol
        * next_chunk_number [unsigned int]

        Parameters:
            bytes: the ACK message received from the server

        Returns:
            ACK_type: the value of the ACK_type field
            next_chunk_number: the number of the next desired chunk
        """
        # TODO: Implement the functionality described in this function's docstring
        ack_type, next_chunk_number = unpack('!BI', bytes)
        return ack_type, next_chunk_number
    

    def compute_hash(self, data):
        """
        Computes a hash for given data using the SHAKE-128 algorithm.

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
            data (bytes): The data to be hashed.
            hash_length (int): The desired length of the hash output.

        Returns:
            bytes: The computed hash.
        """
        # TODO: Implement the functionality described in this function's docstring
        hash_obj = hashlib.shake_128()
        hash_obj.update(data)
        return hash_obj.digest(self.hash_length)

    def shutdown(self):
        """
        Shuts down the client by stopping its operation and closing the socket.

        This method is responsible for cleanly terminating the client's operation.
        It indicates that the client is no longer in operation. If the client has an 
        active socket connection, it closes the socket to ensure proper release of 
        resources and network cleanup.

        The method logs the shutdown process, providing visibility into the client's
        state transitions. It's designed to be safely callable even if the socket is
        already closed or not initialized, preventing any unexpected exceptions during
        the shutdown process.

        Usage Example:
            client = FileTransferClient('192.168.1.10', 12345)
            if client.start():
                client.send_file('test1.jpg')
                client.shutdown()

        Note:
            - Call this method to cleanly shut down the client after use or in case of an error.
            - Do NOT set client_socket to None in this method. The autograder will examine
                client_socket to ensure it is closed properly.
        """
        self.logger.info("Client is shutting down...")

        # TODO: Implement the functionality described in this function's docstring

        if self.client_socket:
            try: 
                self.client_socket.close() 
                self.logger.info("Socket closed successfully.")
            except OSError as e:
                self.logger.error(f"Error while closing socket: {e}")
        self.logger.removeHandler(self.handler)


if __name__ == "__main__":
    print("[DEBUG] client.py is running...")
    client = FileTransferClient("localhost", 5000)
    if client.start():
        client.send_file("source/test1.jpg")
        client.send_file("source/test2.jpg")
        client.shutdown()

#ifndef __VOLATILE_METADATA_C_API_H__
#define __VOLATILE_METADATA_C_API_H__

#include <stdint.h>

#include "decafs_types/file_types.h"
#include "decafs_types/ip_address.h"

/*
 * Returns the chunk size that is set for this instance of DecaFS.
 * If chunk size has not been set yet, this function returns 0.
 */
extern "C" uint32_t get_chunk_size ();

/*
 * Sets the chunk size for this instance of DecaFS.
 * If chunk size has already been set, SIZE_ALREADY_SET is returned.
 * If the chunk size provided is an invalid size SIZE_INVALID is returned.
 */
extern "C" int set_chunk_size (uint32_t size);

/*
 * Returns the stripe size that is set for this instance of DecaFS.
 * If stripe size has not been set yet, this function returns 0.
 */
extern "C" uint32_t get_stripe_size ();

/*
 * Sets the stripe size for this instance of DecaFS.
 * If stripe size has already been set, SIZE_ALREADY_SET is returned.
 * If the stripe size provided is an invalid size SIZE_INVALID is returned.
 */
extern "C" int set_stripe_size (uint32_t size);

/*
 * Returns the node number for a specific IP address.
 * If barista_core was not started with the given IP address, IP_NOT_FOUND
 *   is returned.
 */
extern "C" uint32_t get_node_number (char *ip);

/*
 * Returns the IP address of the node with a given node number.
 * If the node number is not found, NODE_NUMBER_NOT_FOUND
 *   is returned.
 */
extern "C" struct ip_address get_node_ip (uint32_t node_number);


/*
 * Add a node ip and node number pairing to the metadata for this instance
 *   of DecaFS.
 * If the ip address has already been assigned a node number, IP_EXISTS
 *   is returned.
 */
extern "C" int add_node (char *ip, uint32_t node_number);

/*
 * Set the node with the specific ip address to be "down" 
 *   of DecaFS.
 * If barista_core was not started with the given IP address, IP_NOT_FOUND
 *   is returned.
 */
extern "C" uint32_t set_node_down (char *ip);

/*
 * Set the node with the specific ip address to be "up" 
 *   of DecaFS.
 * If barista_core was not started with the given IP address, IP_NOT_FOUND
 *   is returned.
 */
extern "C" uint32_t set_node_up (char *ip);

/* 
 * Determines whether or not a specific node is "up"
 */
extern "C" bool is_node_up (char *ip);

/*
 * Give the "state" of the system.
 * nodes is filled in with the ip addresses for the active nodes (nodes
 *   that were not set to "down").
 * IP addresses of each node will be returned in sorted order.
 * nodes will be reallocated to support the number of nodes that are up.
 * The number of active nodes in the system is returned.
 */
extern "C" int get_active_node_count();

/*
 * Give the "state" of the system.
 * nodes is filled in with the ip addresses for the active nodes (nodes
 *   that were not set to "down").
 * IP addresses of each node will be returned in sorted order.
 * nodes will be reallocated to support the number of nodes that are up.
 * The number of active nodes in the system is returned.
 */
extern "C" uint32_t get_active_nodes (char ***nodes);
    
/*
 * Determines whether or not a node exists in the system.
 * @return true if node exists, else false
 */
extern "C" bool node_exists (uint32_t node_number);

/*
 *   Start a new file cursor if one doesn’t exist already.
 *  @return the fd
 */
extern "C" int new_file_cursor (uint32_t file_id, struct client client);

/*
 *   Remove a file cursor for an open instance of a file.
 *   @return id of the file closed on success
 *   @return INSTANCE_NOT_FOUND if fd does not exist
 *   @return WRONG_CLIENT if the client doesn't match the client who
 *           opened the file
 */
extern "C" int close_file_cursor (uint32_t fd, struct client client);

/*
 * Provides information about the cursor for an instance of an open
 *   file.
 *  @return the current byte offset for a given fd
 *          if the fd does not exist, INSTANCE_NOT_FOUND is returned.
 */
extern "C" int get_file_cursor (uint32_t fd);

/*
 *   Set the cursor for an instance of an open file.
 *  @return the current byte offset for a given fd
 *          if the fd does not exist, INSTANCE_NOT_FOUND is returned.
 */
extern "C" int set_file_cursor (uint32_t fd, uint32_t offset, struct client client);
    
/*
 * Find the file_instance associated with a given fd.
 */
extern "C" struct file_instance get_file_info (uint32_t fd);

#endif
#pragma once

bool BypassDNS = true;

bool (*oDns_cctor)(void *unk);
bool Dns_cctor(void *unk)
{
    if (BypassDNS) {
        return true;
    }
    return oDns_cctor(unk);
}

bool (*oDns_GetHostByName_internal)(void *unk, string host, string h_name, string h_aliases, string h_addr_list);
bool Dns_GetHostByName_internal(void *unk, string host, string h_name, string h_aliases, string h_addr_list) {
    if (BypassDNS) {
    return oDns_GetHostByName_internal(unk, "ip.ml.youngjoygame.com:30220", "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com");
    }
    return oDns_GetHostByName_internal(unk, host, h_name, h_aliases, h_addr_list);
}    

bool (*oDns_GetHostByAddr_internal)(void * unk, string host, string h_name, string h_aliases, string h_addr_list);
bool Dns_GetHostByAddr_internal(void * unk, string host, string h_name, string h_aliases, string h_addr_list) {
    if (BypassDNS) {
    return oDns_GetHostByAddr_internal(unk, "ip.ml.youngjoygame.com:30220", "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com");
    }
    return oDns_GetHostByAddr_internal(unk, host, h_name, h_aliases, h_addr_list);
}    

bool (*oDns_hostent_to_IPHostEntry)(void * unk, string h_name, string h_aliases, string h_addrlist);
bool Dns_hostent_to_IPHostEntry(void * unk, string h_name, string h_aliases, string h_addrlist) {
    if (BypassDNS) {
    return oDns_hostent_to_IPHostEntry(unk, "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com", "ip.ml.youngjoygame.com");
    }
    return oDns_hostent_to_IPHostEntry(unk, h_name, h_aliases, h_addrlist);
}    

bool (*oDns_GetHostByAddressFromString)(void * unk, string address);
bool Dns_GetHostByAddressFromString(void * unk, string address) {
    if (BypassDNS) {
    return oDns_GetHostByAddressFromString(unk, "127.0.0.1");
    }
    return oDns_GetHostByAddressFromString(unk, address);
}    
   
bool (*oDns_GetHostEntry)(void * unk, string hostNameOrAddress);
bool Dns_GetHostEntry(void * unk, string hostNameOrAddress) {
    if (BypassDNS) {
    return oDns_GetHostEntry(unk, "ip.ml.youngjoygame.com:30220");
    }
    return oDns_GetHostEntry(unk, hostNameOrAddress);
}    

bool (*oDns_GetHostAddresses)(void * unk, string hostNameOrAddress);
bool Dns_GetHostAddresses(void * unk, string hostNameOrAddress) {
    if (BypassDNS) {
    return oDns_GetHostAddresses(unk, "ip.ml.youngjoygame.com:30220");
    }
    return oDns_GetHostAddresses(unk, hostNameOrAddress);
}    
        
bool (*oDns_GetHostByName)(void * unk, string hostNameOrAddress);
bool Dns_GetHostByName(void * unk, string hostNameOrAddress) {
    if (BypassDNS) {
    return oDns_GetHostByName(unk, "ip.ml.youngjoygame.com:30220");
    }
    return oDns_GetHostByName(unk, hostNameOrAddress);
}

void (*oDisposeServerObject)() = 0;
void DisposeServerObject(void* unk) {
    return;
}

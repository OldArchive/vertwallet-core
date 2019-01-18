//
//  BRChainParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRChainParams_h
#define BRChainParams_h

#include "BRMerkleBlock.h"
#include <assert.h>

typedef struct {
    uint32_t height;
    UInt256 hash;
    uint32_t timestamp;
    uint32_t target;
} BRCheckPoint;

typedef struct {
    const char * const *dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRMerkleBlock *previous, uint32_t transitionTime);
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;

static const char *BRMainNetDNSSeeds[] = {
    "useast1.vtconline.org.", // James Lovejoy
    "vtc.gertjaap.org.", // Gert-Jaap Glasbergen
    "seed.vtc.bryangoodson.org.", // Bryan Goodson
    "seed.orderofthetaco.org.", // Eric (etang600)
    "dnsseed.pknight.ca.", // pknight
    "seed.alexturek.org.", // Alex Turek
    "vertcoin.mbl.cash." // jk_14
};

static const char *BRTestNetDNSSeeds[] = {
        "digiexplorer.info",
		"digihash.co",
		"seed.vertcoin.io",
        "seed1.vertcoin.io",
        "seed2.vertcoin.io",
        "seed3.vertcoin.io", NULL
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {

        {      0, uint256("4d96a915f49d40b1e5c2844d1ee2dccb90013a990ccea12c492d22110489f0c4"), 1389311371, 0x1e0ffff0 },
        {  24200, uint256("d7ed819858011474c8b0cae4ad0b9bdbb745becc4c386bc22d1220cc5a4d1787"), 1390701333, 0x1c130a52 },
        {  65000, uint256("9e673a69c35a423f736ab66f9a195d7c42f979847a729c0f3cef2c0b8b9d0289"), 1396856613, 0x1c013819 },
        {  84065, uint256("a904170a5a98109b2909379d9bc03ef97a6b44d5dafbc9084b8699b0cba5aa98"), 1399714612, 0x1c010fd5 },
        { 228023, uint256("15c94667a9e941359d2ee6527e2876db1b5e7510a5ded3885ca02e7e0f516b51"), 1421367388, 0x1c02bba5 },
        { 346992, uint256("f1714fa4c7990f4b3d472eb22132891ccd3c7ad7208e2d1ab15bde68854fb0ee"), 1439188880, 0x1c012830 },
        { 347269, uint256("fa1e592b7ea2aa97c5f20ccd7c40f3aaaeb31d1232c978847a79f28f83b6c22a"), 1439231038, 0x1c01bf9c },
        { 430000, uint256("2f5703cf7b6f956b84fd49948cbf49dc164cfcb5a7b55903b1c4f53bc7851611"), 1451641736, 0x1c00a632 },
        { 516999, uint256("572ed47da461743bcae526542053e7bc532de299345e4f51d77786f2870b7b28"), 1464732960, 0x1c011edd }

};

static const BRCheckPoint BRTestNetCheckpoints[] = {
        {       0, uint256("cee8f24feb7a64c8f07916976aa4855decac79b6741a8ec2e32e2747497ad2c9"), 1481291250, 0x1e0ffff0 },
        {   10000, uint256("e84a668d907d002e013da912ac2d919e8613f97221ab0505a272b2e8dd6a71d8"), 1510280787, 0x1e01aa34 }
};

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRMerkleBlock *previous, uint32_t transitionTime)
{
    int r = 1;
    
    assert(block != NULL);
    
    if (! previous || !UInt256Eq(block->prevBlock, previous->blockHash) || block->height != previous->height + 1)
        r = 0;
    
    return r;
}

static const BRChainParams BRMainNetParams = {
    BRMainNetDNSSeeds,
    5889,       // standardPort
    0xdab5bffa, // magicNumber
    0,          // services
    BRMerkleBlockVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};

static const BRChainParams BRTestNetParams = {
    BRTestNetDNSSeeds,
    12025,      // standardPort
    0xdab6c3fa, // magicNumber
    0,          // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints)
};

#endif // BRChainParams_h

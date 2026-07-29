// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2020 The BitQube Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITQUBE_CHAINPARAMS_H
#define BITQUBE_CHAINPARAMS_H

#include "chainparamsbase.h"
#include "consensus/params.h"
#include "primitives/block.h"
#include "protocol.h"

#include <memory>
#include <vector>

struct CDNSSeedData {
    std::string host;
    bool supportsServiceBitsFiltering;
    CDNSSeedData(const std::string &strHost, bool supportsServiceBitsFilteringIn) : host(strHost), supportsServiceBitsFiltering(supportsServiceBitsFilteringIn) {}
};

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

typedef std::map<int, uint256> MapCheckpoints;

struct CCheckpointData {
    MapCheckpoints mapCheckpoints;
};

struct ChainTxData {
    int64_t nTime;
    int64_t nTxCount;
    double dTxRate;
};

/**
 * CChainParams defines various tweakable parameters of a given instance of the
 * BitQube system. There are three: the main network on which people trade goods
 * and services, the public test network which gets reset from time to time and
 * a regression test mode which is intended for private networks only. It has
 * minimal difficulty to ensure that blocks can be found instantly.
 */
class CChainParams
{
public:
    enum Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,
        EXT_PUBLIC_KEY,
        EXT_SECRET_KEY,

        MAX_BASE58_TYPES
    };

    const Consensus::Params& GetConsensus() const { return consensus; }
    const CMessageHeader::MessageStartChars& MessageStart() const { return pchMessageStart; }
    int GetDefaultPort() const { return nDefaultPort; }

    bool MiningRequiresPeers() const {return fMiningRequiresPeers; }
    const CBlock& GenesisBlock() const { return genesis; }
    /** Default value for -checkmempool and -checkblockindex argument */
    bool DefaultConsistencyChecks() const { return fDefaultConsistencyChecks; }
    /** Policy: Filter transactions that do not match well-defined patterns */
    bool RequireStandard() const { return fRequireStandard; }
    uint64_t PruneAfterHeight() const { return nPruneAfterHeight; }
    /** Make miner stop after a block is found. In RPC, don't return until nGenProcLimit blocks are generated */
    bool MineBlocksOnDemand() const { return fMineBlocksOnDemand; }
    /** Return the BIP70 network string (main, test or regtest) */
    std::string NetworkIDString() const { return strNetworkID; }
    const std::vector<CDNSSeedData>& DNSSeeds() const { return vSeeds; }
    const std::vector<unsigned char>& Base58Prefix(Base58Type type) const { return base58Prefixes[type]; }
    int ExtCoinType() const { return nExtCoinType; }
    const std::vector<SeedSpec6>& FixedSeeds() const { return vFixedSeeds; }
    const CCheckpointData& Checkpoints() const { return checkpointData; }
    const ChainTxData& TxData() const { return chainTxData; }
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout);
    void TurnOffSegwit();
    void TurnOffCSV();
    void TurnOffBIP34();
    void TurnOffBIP65();
    void TurnOffBIP66();
    bool BIP34();
    bool BIP65();
    bool BIP66();
    bool CSVEnabled() const;

    /** BTQ Start **/
    const CAmount& IssueAssetBurnAmount() const { return nIssueAssetBurnAmount; }
    const CAmount& ReissueAssetBurnAmount() const { return nReissueAssetBurnAmount; }
    const CAmount& IssueSubAssetBurnAmount() const { return nIssueSubAssetBurnAmount; }
    const CAmount& IssueUniqueAssetBurnAmount() const { return nIssueUniqueAssetBurnAmount; }
    const CAmount& IssueMsgChannelAssetBurnAmount() const { return nIssueMsgChannelAssetBurnAmount; }
    const CAmount& IssueQualifierAssetBurnAmount() const { return nIssueQualifierAssetBurnAmount; }
    const CAmount& IssueSubQualifierAssetBurnAmount() const { return nIssueSubQualifierAssetBurnAmount; }
    const CAmount& IssueRestrictedAssetBurnAmount() const { return nIssueRestrictedAssetBurnAmount; }
    const CAmount& AddNullQualifierTagBurnAmount() const { return nAddNullQualifierTagBurnAmount; }

    const std::string& IssueAssetFeeAddress() const { return strIssueAssetFeeAddress; }
    const std::string& ReissueAssetFeeAddress() const { return strReissueAssetFeeAddress; }
    const std::string& IssueSubAssetFeeAddress() const { return strIssueSubAssetFeeAddress; }
    const std::string& IssueUniqueAssetFeeAddress() const { return strIssueUniqueAssetFeeAddress; }
    const std::string& IssueMsgChannelAssetFeeAddress() const { return strIssueMsgChannelAssetFeeAddress; }
    const std::string& IssueQualifierAssetFeeAddress() const { return strIssueQualifierAssetFeeAddress; }
    const std::string& IssueSubQualifierAssetFeeAddress() const { return strIssueSubQualifierAssetFeeAddress; }
    const std::string& IssueRestrictedAssetFeeAddress() const { return strIssueRestrictedAssetFeeAddress; }
    const std::string& AddNullQualifierTagFeeAddress() const { return strAddNullQualifierTagFeeAddress; }
    const std::string& GlobalFeeAddress() const { return strGlobalFeeAddress; }

    //  Indicates whether or not the provided address is a burn address
    bool IsFeeAddress(const std::string & p_address) const
    {
        if (
            p_address == strIssueAssetFeeAddress
            || p_address == strReissueAssetFeeAddress
            || p_address == strIssueSubAssetFeeAddress
            || p_address == strIssueUniqueAssetFeeAddress
            || p_address == strIssueMsgChannelAssetFeeAddress
            || p_address == strIssueQualifierAssetFeeAddress
            || p_address == strIssueSubQualifierAssetFeeAddress
            || p_address == strIssueRestrictedAssetFeeAddress
            || p_address == strAddNullQualifierTagFeeAddress
            || p_address == strGlobalFeeAddress
        ) {
            return true;
        }

        return false;
    }

    unsigned int DGWActivationBlock() const { return nDGWActivationBlock; }
    unsigned int MessagingActivationBlock() const { return nMessagingActivationBlock; }
    unsigned int RestrictedActivationBlock() const { return nRestrictedActivationBlock; }

    int MaxReorganizationDepth() const { return nMaxReorganizationDepth; }
    int MinReorganizationPeers() const { return nMinReorganizationPeers; }
    int MinReorganizationAge() const { return nMinReorganizationAge; }

    int GetAssetActivationHeight() const { return nAssetActivationHeight; }
    /** BTQ End **/

protected:
    CChainParams() {}

    Consensus::Params consensus;
    CMessageHeader::MessageStartChars pchMessageStart;
    int nDefaultPort;
    uint64_t nPruneAfterHeight;
    std::vector<CDNSSeedData> vSeeds;
    std::vector<unsigned char> base58Prefixes[MAX_BASE58_TYPES];
    int nExtCoinType;
    std::string strNetworkID;
    CBlock genesis;
    std::vector<SeedSpec6> vFixedSeeds;
    bool fDefaultConsistencyChecks;
    bool fRequireStandard;
    bool fMineBlocksOnDemand;
    bool fMiningRequiresPeers;
    CCheckpointData checkpointData;
    ChainTxData chainTxData;

    /** BTQ Start **/
    // Burn Amounts
    CAmount nIssueAssetBurnAmount;
    CAmount nReissueAssetBurnAmount;
    CAmount nIssueSubAssetBurnAmount;
    CAmount nIssueUniqueAssetBurnAmount;
    CAmount nIssueMsgChannelAssetBurnAmount;
    CAmount nIssueQualifierAssetBurnAmount;
    CAmount nIssueSubQualifierAssetBurnAmount;
    CAmount nIssueRestrictedAssetBurnAmount;
    CAmount nAddNullQualifierTagBurnAmount;

    // Burn Addresses
    std::string strIssueAssetFeeAddress;
    std::string strReissueAssetFeeAddress;
    std::string strIssueSubAssetFeeAddress;
    std::string strIssueUniqueAssetFeeAddress;
    std::string strIssueMsgChannelAssetFeeAddress;
    std::string strIssueQualifierAssetFeeAddress;
    std::string strIssueSubQualifierAssetFeeAddress;
    std::string strIssueRestrictedAssetFeeAddress;
    std::string strAddNullQualifierTagFeeAddress;

    // Global Burn Address
    std::string strGlobalFeeAddress;

    unsigned int nDGWActivationBlock;
    unsigned int nMessagingActivationBlock;
    unsigned int nRestrictedActivationBlock;

    int nMaxReorganizationDepth;
    int nMinReorganizationPeers;
    int nMinReorganizationAge;

    int nAssetActivationHeight;

    uint32_t nKAAAWWWPOWActivationTime;
    /** BTQ End **/
};

/**
 * Creates and returns a std::unique_ptr<CChainParams> of the chosen chain.
 * @returns a CChainParams* of the chosen chain.
 * @throws a std::runtime_error if the chain is not supported.
 */
std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain);

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CChainParams &GetParams();

/**
 * Sets the params returned by Params() to those for the given BIP70 chain name.
 * @throws std::runtime_error when the chain is not supported.
 */
void SelectParams(const std::string& chain, bool fForceBlockNetwork = false);

/**
 * Allows modifying the Version Bits regtest parameters.
 */
void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout);

void TurnOffSegwit();

void TurnOffBIP34();

void TurnOffBIP65();

void TurnOffBIP66();

void TurnOffCSV();

#endif // BITQUBE_CHAINPARAMS_H

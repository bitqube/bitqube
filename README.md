<p align="center">
  <img src="bitqube-logo.png" alt="BitQube" width="160">
</p>

# BitQube Core (BTQ)

**Mine · Participate · Transact**

BitQube (BTQ) is a Proof-of-Work digital asset built for fair distribution, a
transparent fixed emission, and long-term ecosystem participation. It is a fork
of [Ravencoin](https://ravencoin.org) (itself derived from Bitcoin), retaining
the full asset/token layer while introducing BitQube's own economics, network,
and branding.

- **Website:** https://bitqube.org
- **Block explorer:** https://explorer.bitqube.org
- **Mining pool:** `stratum+tcp://5.78.79.98:10032` (KawPoW)
- **Source:** https://github.com/bitqube/bitqube
- **Consensus:** Proof of Work — **KawPoW** (GPU-friendly, ASIC-resistant)
- **Block time:** 1 minute
- **Max supply:** 8,000,000 BTQ (fixed — no inflation after emission ends)

---

## Key parameters

| | |
|---|---|
| Coin name / ticker | BitQube / **BTQ** |
| Smallest unit | **Bit** (1 BTQ = 100,000,000 Bits) · 8 decimals |
| Max supply | **8,000,000 BTQ** |
| Block time | 1 minute (525,600 blocks/year) |
| PoW algorithm | KawPoW (from launch) |
| Community mining | 7,358,400 BTQ (91.98%) |
| Ecosystem Reserve | 641,600 BTQ (8.02%, minted in block 1) |
| Mainnet P2P port | 8851 |
| Testnet P2P port | 18851 |
| Address prefix | `B` (P2PKH), `b` (P2SH) |
| DNS seed | seed.bitqube.org |

## Emission schedule

An 8-phase, 8-year step-down. After the final mined block (**4,204,799**) no new
BTQ is ever created; miners continue to earn transaction fees.

| Phase / Year | Block range | Reward/block | BTQ generated |
|---|---|---|---|
| 1 | 0 – 525,599 | 3.5 BTQ | 1,839,600 |
| 2 | 525,600 – 1,051,199 | 2.8 BTQ | 1,471,680 |
| 3 | 1,051,200 – 1,576,799 | 2.2 BTQ | 1,156,320 |
| 4 | 1,576,800 – 2,102,399 | 1.8 BTQ | 946,080 |
| 5 | 2,102,400 – 2,627,999 | 1.4 BTQ | 735,840 |
| 6 | 2,628,000 – 3,153,599 | 1.1 BTQ | 578,160 |
| 7 | 3,153,600 – 3,679,199 | 0.9 BTQ | 473,040 |
| 8 | 3,679,200 – 4,204,799 | 0.3 BTQ | 157,680 |

Block **1** additionally mints the **641,600 BTQ Ecosystem Reserve** premine
(development, infrastructure, security, partnerships, listings). Mined emission
(7,358,400) + reserve (641,600) = **8,000,000 BTQ** exactly.

> **Launch note:** the first **5,000 blocks** are pinned to a low difficulty
> floor so the network can be bootstrapped with CPU mining, after which the Dark
> Gravity Wave retarget takes over.

---

## Consensus & activation heights

BitQube is Proof-of-Work (**KawPoW**) with Dark Gravity Wave difficulty
retargeting and hard-coded block checkpoints. Consensus-critical mainnet
activation heights:

| Feature | Height | Notes |
|---|---|---|
| Low-difficulty bootstrap floor | 0 – 5,000 | CPU-mineable launch window |
| Asset layer (issue / reissue / transfer / unique / restricted / qualifier / messaging) | **6,700** | assets become active |
| Asset issuance-fee reduction | **8,400** | fees drop to the reduced schedule below |

### Asset issuance fees

Issuing an asset burns a fee to the network fee address. The fee change is
**height-gated** so the pre-8,400 chain history stays valid: below block 8,400
the original (higher) fees applied; from block **8,400** onward the reduced
fees below apply.

| Operation | Fee (BTQ) |
|---|---|
| Issue main asset | 5 |
| Issue sub-asset | 1 |
| Issue unique asset | 0.1 |
| Reissue | 1 |
| Messaging channel | 1 |
| Qualifier | 10 |
| Sub-qualifier | 1 |
| Restricted asset | 20 |
| Add null-qualifier tag | 0.01 |

> **Node operators:** the fee reduction is a consensus rule. Every node (seed
> nodes, pool, wallets) must run **v1.1.0 or later** before block 8,400, and no
> new asset should be issued until all nodes are upgraded — a fee mismatch
> between old and new nodes will fork the chain.

---

## Binaries

BitQube ships the standard Bitcoin/Ravencoin binary set:

- `bitqubed` — full node daemon
- `bitqube-cli` — RPC command-line client
- `bitqube-qt` — desktop wallet (GUI)

## Running a daemon

The data directory is `~/.bitqube` (created on first run). Network defaults:

| | Mainnet | Testnet |
|---|---|---|
| P2P port | 8851 | 18851 |
| RPC port | 8766 | 18766 |

**1. Create `~/.bitqube/bitqube.conf`:**

```ini
# run as a background daemon
daemon=1
# accept RPC from the CLI on this machine
server=1
rpcuser=changeThisUser
rpcpassword=changeThisToALongRandomSecret
# uncomment to accept inbound connections and help the network
# listen=1
# (optional) index every transaction, needed by explorers
# txindex=1
```

**2. Start it and check status:**

```bash
bitqubed -daemon                     # start in the background
bitqube-cli getblockchaininfo        # sync status / height
bitqube-cli getpeerinfo              # connected peers
bitqube-cli getnewaddress            # a wallet address (starts with 'B')
bitqube-cli getwalletinfo            # balance, etc.
bitqube-cli stop                     # shut the daemon down cleanly
```

New nodes bootstrap automatically from `seed.bitqube.org` plus the hard-coded
fixed seeds. To help the network, open **TCP port 8851** to the internet and set
`listen=1`. On a server, run `bitqubed` under `systemd` (or `screen`/`tmux`) so
it survives logout; verify progress with `bitqube-cli getblockchaininfo`
(`"verificationprogress"` near `1.0` means fully synced).

## Building from source (Ubuntu/Debian)

Install dependencies, then build:

```bash
sudo apt-get install build-essential libtool autotools-dev automake pkg-config \
     bsdmainutils python3 libssl-dev libevent-dev libboost-all-dev \
     libminiupnpc-dev libzmq3-dev libdb++-dev libqt5gui5 libqt5core5a \
     libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev

./autogen.sh
./configure
make -j"$(nproc)"
```

> The wallet requires **Berkeley DB 4.8**. If your distro lacks it, either use
> `contrib/install_db4.sh` or configure with `--with-incompatible-bdb`.

### Portable (static) release binaries

To produce self-contained binaries that run on a bare server with no dependency
installation (this is how release binaries are built), use the `depends` system:

```bash
cd depends
make HOST=x86_64-pc-linux-gnu NO_QT=1 -j"$(nproc)"      # builds static deps
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site \
    ./configure --prefix=/ --without-gui
make -j"$(nproc)"
```

The resulting `bitqubed` / `bitqube-cli` link their dependencies statically and
require only `glibc`. (Omit `NO_QT=1` / `--without-gui` to also build the
portable `bitqube-qt`. Cross-compiling Windows and macOS release binaries is
supported via the same `depends` system with the appropriate `HOST=`.)

## Mining

BitQube uses **KawPoW**, so any standard KawPoW GPU miner (T-Rex, kawpowminer,
NBMiner, etc.) works. The low launch difficulty makes the first blocks
CPU-mineable for bootstrapping.

### Pool mining (recommended)

Public pool: **`stratum+tcp://5.78.79.98`** — three ports for different
difficulty tiers: **`10008`** (low), **`10032`** (medium), **`10256`** (high).
Pick the port that matches your hashrate.

Example with T-Rex:

```bash
t-rex -a kawpow \
      -o stratum+tcp://5.78.79.98:10032 \
      -u <YOUR_BTQ_ADDRESS> \
      -p x -w rig1
```

Your `<YOUR_BTQ_ADDRESS>` is any BitQube address (starts with `B`) from
`bitqube-cli getnewaddress` or the Qt wallet. Track workers and payouts on the
pool's web dashboard and confirm coins in the [block explorer](https://explorer.bitqube.org).

### Solo mining

Point the miner at your own synced `bitqubed` (with `server=1` and RPC
credentials set) instead of the pool address.

## Assets

BitQube inherits Ravencoin's asset layer — issue, reissue, transfer, unique,
restricted, and qualifier assets, plus messaging. Explore them via the
`Create Assets` / `Manage Assets` tabs in the GUI or the `*asset*` RPCs.

## License

BitQube Core is released under the terms of the MIT license. See
[COPYING](COPYING) or https://opensource.org/licenses/MIT.

## Acknowledgements

BitQube stands on the work of the Bitcoin and Ravencoin developers. Deep thanks
to both communities for the secure, open-source foundation this project builds on.

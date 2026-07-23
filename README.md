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

## Binaries

BitQube ships the standard Bitcoin/Ravencoin binary set:

- `bitqubed` — full node daemon
- `bitqube-cli` — RPC command-line client
- `bitqube-tx` — transaction construction utility
- `bitqube-qt` — desktop wallet (GUI)

## Running a node

```bash
# start the daemon
bitqubed -daemon

# basic queries
bitqube-cli getblockchaininfo
bitqube-cli getpeerinfo

# a wallet address (starts with 'B')
bitqube-cli getnewaddress
```

To help the network, run a listening node with **TCP port 8851** open to the
internet. New nodes bootstrap from `seed.bitqube.org` plus the hardcoded fixed
seeds.

## Building from source (Ubuntu/Debian)

Install dependencies, then build:

```bash
sudo apt-get install build-essential libtool autotools-dev automake pkg-config \
     bsdmainutils python3 libssl-dev libevent-dev libboost-all-dev \
     libminiupnpc-dev libzmq3-dev libdb++-dev libqt5gui5 libqt5core5a \
     libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev

./autogen.sh
./configure --with-tx
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
    ./configure --prefix=/ --with-tx --without-gui
make -j"$(nproc)"
```

The resulting `bitqubed` / `bitqube-cli` / `bitqube-tx` link their dependencies
statically and require only `glibc`.

## Mining

BitQube uses **KawPoW**, so standard KawPoW GPU miners (e.g. kawpowminer,
T-Rex, NBMiner) work by pointing them at a `bitqubed` node or a pool. The low
launch difficulty makes the first blocks CPU-mineable for bootstrapping.

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

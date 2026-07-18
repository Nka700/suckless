# 技術スタック

## コア技術

- **Ansible** — 構成管理・自動化ツール（Playbook ベース）
- **YAML** — Playbook、変数ファイル、タスク定義の記述言語
- **Jinja2** — テンプレートエンジン（`.j2` ファイル）

## パッケージマネージャ

| ディストリビューション | パッケージマネージャ | Ansible モジュール |
|---|---|---|
| Arch Linux | pacman | `pacman` |
| Debian | apt | `apt` |

## 主要ツール・ソフトウェア

- **suckless ツール群**: dwm, dmenu, st, slstatus（ソースからビルド、`make clean install`）
- **GNU Stow**: dotfiles のシンボリックリンク管理
- **zsh + zplug**: シェル環境
- **TLP**: 電源管理
- **yay**: AUR ヘルパー（Arch のみ、`makepkg` でビルド）
- **ly**: ログインマネージャ（Arch）
- **lightdm**: ログインマネージャ（Debian）

## よく使うコマンド

### Playbook 実行（リモートホスト）

```sh
ansible-playbook -i ${IP}, main.yml \
  --extra-vars "username=${USER} upassword=${PASS}" \
  --user ${ANSIBLE_USER} --ask-pass --ask-become-pass
```

### Playbook 実行（ローカル、Debian のみ）

```sh
ansible-playbook -i localhost, -c local main.yml \
  --extra-vars "username=${USER} upassword=${PASS}" \
  --ask-become-pass
```

### 構文チェック

```sh
ansible-playbook main.yml --syntax-check
```

### ドライラン

```sh
ansible-playbook -i ${IP}, main.yml --check --diff \
  --extra-vars "username=${USER} upassword=${PASS}" \
  --user ${ANSIBLE_USER} --ask-pass --ask-become-pass
```

## 必須変数（`--extra-vars` で渡す）

- `username` — 作成するユーザー名
- `upassword` — ユーザーパスワード（`password_hash('sha512')` でハッシュ化される）

## 設定変数

各 Playbook の `group_vars/all.yml` で以下を制御:

| 変数名 | 型 | 説明 | Arch | Debian |
|---|---|---|---|---|
| `setup_zsh` | bool | zsh セットアップの有無 | ✓ | ✓ |
| `install_dwm` | bool | dwm インストールの有無 | ✓ | ✓ |
| `browser` | string | ブラウザ選択（chromium, firefox, vivaldi, brave） | ✓ | — |
| `pull_dotfiles` | bool | dotfiles クローンの有無 | ✓ | ✓ |
| `configure_tlp` | bool | TLP 設定の有無 | ✓ | ✓ |
| `use_aur` | bool | AUR ヘルパー使用の有無 | ✓ | — |
| `install_terminal_browsers` | bool | ターミナルブラウザの有無 | ✓ | — |
| `install_office` | bool | LibreOffice インストールの有無 | ✓ | — |
| `install_pythonpkg` | bool | Python パッケージインストールの有無 | ✓ | — |

## Ansible 設定（ansible.cfg）

- SSH 接続: `ControlMaster=auto`, `ControlPersist=60s`
- ホストキーチェック無効化: `StrictHostKeyChecking=no`
- インベントリ: `./hosts`（コマンドラインで `-i` 指定が一般的）

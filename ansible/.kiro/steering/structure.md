# プロジェクト構成

## ディレクトリ構造

```
.
├── ansible-arch-dwm-setup/       # Arch Linux 用 Playbook
│   ├── ansible.cfg               # Ansible 設定
│   ├── main.yml                  # メイン Playbook（エントリポイント）
│   ├── group_vars/
│   │   └── all.yml               # 全ホスト共通変数
│   └── roles/                    # Ansible ロール群
│       ├── aur/                  # AUR ヘルパー (yay) インストール
│       ├── authorized_keys/      # SSH 公開鍵配置
│       ├── chromium/             # Chromium ブラウザ
│       ├── core-apps/            # 基本パッケージ群
│       ├── dotfiles/             # dotfiles 展開 (stow)
│       ├── dwm/                  # suckless ツール群ビルド + ly 設定
│       ├── firefox/              # Firefox ブラウザ
│       ├── group/                # グループ管理
│       ├── pacman/               # pacman 設定
│       ├── power-management/     # TLP 設定
│       ├── pythonpkg/            # Python パッケージ
│       ├── reboot/               # リブート（現在コメントアウト）
│       ├── sshd/                 # SSH ハードニング
│       ├── terminal_browsers/    # ターミナルブラウザ (elinks, w3m)
│       ├── user/                 # ユーザー作成 + sudoers
│       └── zsh/                  # zsh + zplug セットアップ
│
├── ansible-debian-dwm-setup/     # Debian 用 Playbook
│   ├── ansible.cfg
│   ├── main.yml
│   ├── group_vars/
│   │   └── all.yml
│   └── roles/
│       ├── authorized_keys/      # SSH 公開鍵配置（現在コメントアウト）
│       ├── core-apps/            # 基本パッケージ群
│       ├── dotfiles/             # dotfiles 展開 (stow)
│       ├── fonts/                # Nerd Fonts インストール
│       ├── group/                # グループ管理
│       ├── power-management/     # TLP 設定
│       ├── sshd/                 # SSH ハードニング
│       ├── suckless/             # suckless ツール群ビルド + lightdm 設定
│       ├── user/                 # ユーザー作成
│       └── zsh/                  # zsh + zplug セットアップ
│
└── .kiro/steering/               # AI アシスタント用ステアリングルール
```

## ロールの内部構造（標準パターン）

```
roles/<role_name>/
├── tasks/
│   └── main.yml        # タスク定義（必須）
├── handlers/
│   └── main.yml        # ハンドラー定義（任意）
└── templates/
    └── *.j2            # Jinja2 テンプレート（任意）
```

## 規約・パターン

### Playbook 構成

- 各ディストリビューション用の Playbook は独立したディレクトリに配置する
- エントリポイントは `main.yml`、`hosts: all` で全ホスト対象
- Arch 版は最初に `pacman: update_cache: yes` で更新チェックを行う play がある
- 変数は `group_vars/all.yml` に集約し、`--extra-vars` で上書き可能にする

### ロール設計

- ロールは単一責務とし、機能ごとに分割する
- 条件付きロールは `when` 句と `group_vars` のブール変数で制御する（`| default(false) | bool` パターン）
- ブラウザロールは `"{{ browser }}"` で変数から動的にロール名を解決する（Arch のみ）

### タスク記述

- タスク名は英語で、何をするか明確に記述する
- `become: yes` は特権が必要なタスクにのみ付与する
- `become_user: "{{ username }}"` でユーザー権限のタスクを実行する
- 外部リポジトリ（dotfiles, suckless）は `git` モジュールで `update: no` を指定し、既存を上書きしない
- suckless ツールのビルドは `make clean install` を `loop` で各ツールに適用する
- テンプレートファイルは `.j2` 拡張子を使用する
- パスワードは `password_hash('sha512')` フィルタでハッシュ化する
- 冪等性チェックには `command` + `register` + `when` パターンを使う（例: yay インストール）

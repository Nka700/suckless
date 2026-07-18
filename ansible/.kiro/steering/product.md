# プロダクト概要

Arch Linux および Debian 向けの dwm (Dynamic Window Manager) デスクトップ環境を自動構築する Ansible Playbook 集。

## 目的

- 新規マシンやクリーンインストール後に、dwm ベースのデスクトップ環境を一発で再現可能にする
- ユーザー作成、パッケージインストール、dotfiles 展開、suckless ツール群のビルド、各種サービス設定を自動化する

## 対象ディストリビューション

- **Arch Linux** (`ansible-arch-dwm-setup/`) — pacman + AUR (yay)
- **Debian** (`ansible-debian-dwm-setup/`) — apt

## 主な構成要素

- ユーザー管理（作成・sudo/wheel 権限付与）
- パッケージ管理（pacman / apt）
- suckless ツール群（dwm, dmenu, st, slstatus）のクローン・ビルド・インストール
- dotfiles の展開（GNU Stow 使用、外部リポジトリからクローン）
- zsh + zplug のセットアップ
- ブラウザ選択（chromium / firefox / vivaldi / brave）
- 電源管理（TLP）
- SSH 設定のハードニング
- AUR ヘルパー（yay）のインストール（Arch のみ）
- Nerd Fonts インストール（Debian のみ）
- ログインマネージャ（Arch: ly、Debian: lightdm）

## 外部依存リポジトリ

- dotfiles: `https://github.com/Nka700/.dotfiles.git`（ブランチはディストリ別）
- suckless: `https://github.com/Nka700/suckless.git`（ブランチはディストリ別）

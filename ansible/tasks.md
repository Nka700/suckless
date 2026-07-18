# 修正タスク一覧

リポジトリ全体を分析し、修正すべき箇所をカテゴリ別にまとめた。

---

## 🔴 重大（動作に影響する問題）

### ~~1. pacman ロールの正規表現が壊れている~~ → 問題なし
- **ファイル**: `ansible-arch-dwm-setup/roles/pacman/tasks/main.yml`
- **結果**: 実ファイルを確認したところ、`$` は正規表現のアンカーであり YAML のクォーティングも正常。修正不要

### 2. `browser` ロールに `when` 条件がない ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/main.yml`
- **修正内容**: `when: browser is defined and browser | length > 0` を追加

### 3. `stow` コマンドが冪等でない ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/roles/dotfiles/tasks/main.yml`、`ansible-debian-dwm-setup/roles/dotfiles/tasks/main.yml`
- **修正内容**: `stow --restow` に変更し、`changed_when: false` を追加

### 4. `make clean install` が冪等でない ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/roles/dwm/tasks/main.yml`、`ansible-debian-dwm-setup/roles/suckless/tasks/main.yml`
- **修正内容**: `changed_when: false` を追加。Debian 側は `shell` → `command` に変更

---

## 🟡 中程度（ベストプラクティス違反・一貫性の問題）

### 5. Ansible モジュールの混在使用 ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/` 配下の全ロール
- **修正内容**: `community.general.pacman` → `pacman` に統一（core-apps, zsh, chromium, firefox, terminal_browsers）

### 6. `ignore_errors: true` の使用 ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/roles/core-apps/tasks/main.yml`
- **修正内容**: `ignore_errors: true` → `failed_when: false` に変更

### 7. Docker リポジトリ追加に `shell` モジュールを使用
- **ファイル**: `ansible-debian-dwm-setup/roles/core-apps/tasks/main.yml`
- **問題**: Docker APT リポジトリの追加に `shell` + ヒアドキュメントを使用。`creates` で冪等性は確保されているが、`apt_repository` モジュールを使うべき
- **修正**: `apt_repository` モジュールに置き換える

### 8. `home_dir` 変数が Arch 側で未定義 ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/group_vars/all.yml`
- **修正内容**: `home_dir: "/home/{{ username }}"` を追加

### 9. `paru` 変数が未使用
- **ファイル**: `ansible-arch-dwm-setup/group_vars/all.yml`
- **問題**: `paru` の設定ブロック（`git_url`, `install_dir`, `build_dir` 等）が定義されているが、どのロールからも参照されていない
- **修正**: 使用予定がなければ削除する。使用予定があればロールを作成する

### 10. `pythonpkg` ロールが空
- **ファイル**: `ansible-arch-dwm-setup/roles/pythonpkg/tasks/main.yml`
- **問題**: 全タスクがコメントアウトされており、ロール自体が何もしない。`core-apps` で `python-pynvim` をインストール済みなので不要
- **修正**: ロールを削除するか、不要であることをコメントで明記する

### 11. `terminal_browsers` ロールの名前と内容が不一致
- **ファイル**: `ansible-arch-dwm-setup/roles/terminal_browsers/tasks/main.yml`
- **問題**: ロール名は `terminal_browsers`（ターミナルブラウザ = elinks, w3m 等）だが、実際にインストールしているのは `terminator` と `kitty`（ターミナルエミュレータ）。ディレクトリ作成タスクも重複している
- **修正**: ロール名を `terminal_emulators` に変更するか、インストールパッケージを修正する。重複タスクを削除する

### 12. `become` の記法が不統一
- **ファイル**: 複数ロール
- **問題**: `become: yes` と `become: True` が混在している（例: `user/tasks/main.yml` では両方使用）
- **修正**: `become: yes` に統一する（Ansible の慣例）

### 13. sshd ハードニングが不十分 ✅ 修正済み
- **ファイル**: `ansible-arch-dwm-setup/roles/sshd/tasks/main.yml`
- **修正内容**: `regexp` を `'^#?PermitRootLogin'` に修正。タスク名を明確化。`notify: restart sshd` を追加

### 14. sshd 設定変更後のサービス再起動がない ✅ 修正済み（Arch のみ）
- **ファイル**: `ansible-arch-dwm-setup/roles/sshd/handlers/main.yml`（新規作成）
- **修正内容**: `restart sshd` ハンドラーを追加
- **未対応**: Debian 側の sshd ロールにも同様の修正が必要

---

## 🟢 軽微（コード品質・メンテナンス性）

### 15. タスク名が不明確
- **ファイル**: 複数
- **問題例**:
  - `edit tlp.conf1` 〜 `edit tlp.conf4` → 何を変更しているか不明
  - `Install yay for users_1` 〜 `users_3` → 連番で意味が分からない
  - `add user docker` → docker グループへの追加なのか、docker ユーザーの追加なのか曖昧
- **修正**: 各タスクの目的が分かる名前にする（例: `Enable TLP service`, `Set USB autosuspend to disabled`）

### 16. `dwm.desktop.j2` が Jinja2 変数を使っていない
- **ファイル**: `ansible-arch-dwm-setup/roles/dwm/templates/dwm.desktop.j2`、`ansible-debian-dwm-setup/roles/suckless/templates/dwm.desktop.j2`
- **問題**: テンプレートファイルだが、Jinja2 変数を一切使用していない。静的ファイルなので `copy` モジュールで十分
- **修正**: `template` → `copy` に変更し、ファイルを `files/dwm.desktop` にリネームする。または将来の拡張性のためにそのまま残す（軽微なので優先度低）

### 17. 空のハンドラーファイルが多数存在
- **ファイル**: 全ロールの `handlers/main.yml`
- **問題**: 全てのハンドラーファイルが `# Handlers for dwm setup` のコメントのみ。使用されていないハンドラーファイルが散在
- **修正**: 不要なハンドラーファイルを削除する。sshd ロールなど必要な箇所にはハンドラーを追加する（タスク14と連動）

### 18. `yay` ロールの `debug` タスクが残っている
- **ファイル**: `ansible-arch-dwm-setup/roles/aur/tasks/main.yml`
- **問題**: `Debug found package` タスクが本番コードに残っている
- **修正**: 削除するか、`verbosity` パラメータを追加して通常実行時は非表示にする（`debug: var=... verbosity=2`）

### 19. `yay` インストールで `sudo pacman -U` をコマンド直書き
- **ファイル**: `ansible-arch-dwm-setup/roles/aur/tasks/main.yml`
- **問題**: `command: sudo pacman -U --noconfirm ...` で `sudo` を直接呼んでいる。`become: yes` が既に設定されているので `sudo` は不要かつ二重権限昇格になる
- **修正**: `sudo` を削除し、`pacman` モジュールの `name` にパッケージパスを指定する

### 20. `paru.build_dir` のパスが `yay` ディレクトリを指している
- **ファイル**: `ansible-arch-dwm-setup/group_vars/all.yml`
- **問題**: `paru.build_dir: /home/{{ username }}/yay` — paru のビルドディレクトリなのに `yay` という名前
- **修正**: タスク9と合わせて、`paru` ブロック自体を削除するか、パスを `/home/{{ username }}/paru` に修正する

### 21. Debian `suckless` ロールで `xrdp` を有効化している
- **ファイル**: `ansible-debian-dwm-setup/roles/suckless/tasks/main.yml`
- **問題**: suckless ツールのビルドロールに `xrdp` サービスの有効化が含まれている。単一責務の原則に反する
- **修正**: `xrdp` 関連タスクを別ロール（例: `xrdp`）に分離するか、`core-apps` に移動する

### 22. `font-cache` の再構築に `become` がない
- **ファイル**: `ansible-debian-dwm-setup/roles/fonts/tasks/main.yml`
- **問題**: `fc-cache -fv` コマンドに `become` も `become_user` もない。ユーザーフォントディレクトリに対して実行するなら `become_user` が必要
- **修正**: `become: yes` + `become_user: "{{ username }}"` を追加する

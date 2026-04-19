# Description
Ansible to build an dwm desktop environment for arch linux.  

# Usage

```sh
ansible-playbook -i ${IP}, main.yml --extra-vars "username=${Your user name} upassword=${Your Password}" --user ${ansible user} --ask-pass --ask-become-pass
```

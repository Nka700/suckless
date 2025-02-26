# Description
Ansible to build an openbox desktop environment for arch linux.  
Needs to run from localhost.  

# Usage

```sh
ansible-playbook -i ${IP}, main.yml --extra-vars "username=${Your user name} upassword=${Your Password}" --user ${ansible user} --ask-pass --ask-become-pass
```

# Description
Ansible to build an dwm desktop environment for Debian.  

# Usage

```sh
ansible-playbook -i ${IP}, main.yml --extra-vars "username=${Your user name} upassword=${Your Password}" --user ${ansible user} --ask-pass --ask-become-pass

# OR

ansible-playbook -i localhost, -c local main.yml --extra-vars "username=${Your user name} upassword=${Your Password}" --ask-become-pass
```

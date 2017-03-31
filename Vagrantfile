# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    config.vm.box = "boxcutter/ubuntu1610-desktop"

    # Share the repo folder with the virtual machine
    # at this path
    config.vm.synced_folder ".", "/home/vagrant/Code/whyte"

    config.vm.provider "virtualbox" do |vb|
        # Display the VirtualBox GUI when booting the machine
        vb.gui = true
    end

    # Set locale
    #
    # This is needed because the vagrant box
    # boxcutter/ubuntu1610-desktop has an incorrect locale.
    config.vm.provision "shell", inline: <<-SHELL
        update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
    SHELL

    # Reload to update the locale
    #
    # This requires the 'vagrant-reload' plugin.
    # Run 'vagrant plugin install vagrant-reload' to install it.
    config.vm.provision :reload

    # Install dependencies
    config.vm.provision "shell", inline: <<-SHELL
        apt-get update
        apt-get install -y libsdl2-dev cmake g++ gdb
    SHELL
end

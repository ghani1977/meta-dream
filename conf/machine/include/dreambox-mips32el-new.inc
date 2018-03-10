# dreambox-mips32el-new.inc

PREFERRED_PROVIDER_virtual/egl ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa-gl"
PREFERRED_PROVIDER_virtual/libgles1 ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/libgles2 ?= "libvc5dream"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa-gl"
PREFERRED_VERSION_linux-dreambox = "3.4"
PREFERRED_VERSION_gnupg ?= "2.1.18"

DISTRO_FEATURES_GFX_mipsel ?= " opengl"

PACKAGECONFIG_pn-glmark2 = "gles2"

PACKAGECONFIG_pn-cogl-1.0 = "egl-kms egl-null \
        ${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'gles2', '', d)}"

PACKAGECONFIG_pn-weston = "${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'gles', '', d)}"

DREAMBOX_IMAGE_SIZE ??= "1024"

IMAGE_FSTYPES =+ "tar.xz"

IMAGE_CMD_tar_prepend = " \
    mkdir -p ${IMAGE_ROOTFS}/tmp; \
    mkdir -p ${IMAGE_ROOTFS}/var/lib/opkg/info; \
    echo "#!/bin/sh" > ${IMAGE_ROOTFS}/var/lib/opkg/info/dreambox-secondstage.postinst; \
    echo "[ -n \"$D\" ] || flash-ssbl /usr/share/dreambox-secondstage/ssbl.bin" >> ${IMAGE_ROOTFS}/var/lib/opkg/info/dreambox-secondstage.postinst; \
    chmod 777 ${IMAGE_ROOTFS}/var/lib/opkg/info/dreambox-secondstage.postinst; \
    rm -f ${DEPLOY_DIR_IMAGE}/.tar.xz; \
    "

IMAGE_CMD_tar_append = " ; \
    cd ${DEPLOY_DIR_IMAGE}; \
    rm -f *.rootfs.manifest; \
    rm -f .manifest; \
    "
package org.godot.godotoculusplatform;

import android.app.Activity;
import android.util.ArraySet;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import org.godotengine.godot.Godot;
import org.godotengine.godot.plugin.GodotPlugin;

import java.util.Set;

public class GodotOculusPlatform extends GodotPlugin {
    private static GodotOculusPlatform singleton;

    static {
        System.loadLibrary("godotoculusplatformA");
    }

    public GodotOculusPlatform(Godot godot) {
        super(godot);
        singleton = this;
    }

    public static GodotOculusPlatform getSingleton() {
        return singleton;
    }

    @NonNull
    @Override
    public String getPluginName() {
        return "GodotOculusPlatform";
    }

    @NonNull
    @Override
    public Set<String> getPluginGDExtensionLibrariesPaths() {
        ArraySet paths = new ArraySet<String>();
        paths.add("addons/godot_oculus_platform/bin/godot_oculus_platform.gdextension");
        return paths;
    }

    @Nullable
    @Override
    public View onMainCreate(Activity activity) {
        initPlatform(activity);
        return super.onMainCreate(activity);
    }

    private native void initPlatform(Activity activity);

}

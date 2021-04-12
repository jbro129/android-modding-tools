.class public Lcom/gbo/banner;
.super Ljava/lang/Object;


# direct methods
.method static constructor <clinit>()V
    .locals 1

    return-void
.end method

.method public constructor <init>()V
    .locals 0

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method

.method public static gboCustomImage(Landroid/content/Context;)V
    .locals 11

    const/4 v0, 0x1

    const-string v1, "Mod By Jbro129"

    invoke-static {p0, v1, v0}, Landroid/widget/Toast;->makeText(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;

    move-result-object v0

    invoke-virtual {v0}, Landroid/widget/Toast;->show()V

    const/4 v10, -0x1

    new-instance v6, Landroid/widget/RelativeLayout;

    invoke-direct {v6, p0}, Landroid/widget/RelativeLayout;-><init>(Landroid/content/Context;)V

    new-instance v4, Landroid/widget/ImageView;

    invoke-direct {v4, p0}, Landroid/widget/ImageView;-><init>(Landroid/content/Context;)V

    :try_start_0
    invoke-virtual {p0}, Landroid/content/Context;->getAssets()Landroid/content/res/AssetManager;

    move-result-object v7

    const-string v8, "config.png"

    invoke-virtual {v7, v8}, Landroid/content/res/AssetManager;->open(Ljava/lang/String;)Ljava/io/InputStream;

    move-result-object v3

    const/4 v7, 0x0

    invoke-static {v3, v7}, Landroid/graphics/drawable/Drawable;->createFromStream(Ljava/io/InputStream;Ljava/lang/String;)Landroid/graphics/drawable/Drawable;

    move-result-object v1

    invoke-virtual {v4, v1}, Landroid/widget/ImageView;->setImageDrawable(Landroid/graphics/drawable/Drawable;)V
    :try_end_0
    .catch Ljava/io/IOException; {:try_start_0 .. :try_end_0} :catch_0

    :goto_0
    new-instance v5, Landroid/widget/RelativeLayout$LayoutParams;

    const/4 v7, -0x2

    invoke-direct {v5, v10, v7}, Landroid/widget/RelativeLayout$LayoutParams;-><init>(II)V

    invoke-virtual {v4, v5}, Landroid/widget/ImageView;->setLayoutParams(Landroid/view/ViewGroup$LayoutParams;)V

    invoke-virtual {v6, v4}, Landroid/widget/RelativeLayout;->addView(Landroid/view/View;)V

    const-string v7, "#373fe8"

    invoke-static {v7}, Landroid/graphics/Color;->parseColor(Ljava/lang/String;)I

    move-result v7

    invoke-virtual {v6, v7}, Landroid/widget/RelativeLayout;->setBackgroundColor(I)V

    new-instance v7, Landroid/app/AlertDialog$Builder;

    invoke-direct {v7, p0}, Landroid/app/AlertDialog$Builder;-><init>(Landroid/content/Context;)V

    invoke-virtual {v7}, Landroid/app/AlertDialog$Builder;->create()Landroid/app/AlertDialog;

    move-result-object v0

    invoke-virtual {v0, v6}, Landroid/app/AlertDialog;->setView(Landroid/view/View;)V

    const/4 v7, 0x0

    invoke-virtual {v0, v7}, Landroid/app/AlertDialog;->setCancelable(Z)V

    const/4 v7, -0x3

    const-string v8, "Subscribe"

    new-instance v9, Lcom/gbo/banner$2;

    invoke-direct {v9, p0}, Lcom/gbo/banner$2;-><init>(Landroid/content/Context;)V

    invoke-virtual {v0, v7, v8, v9}, Landroid/app/AlertDialog;->setButton(ILjava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)V

    const/4 v7, -0x2

    const-string v8, "Continue"

    new-instance v9, Lcom/gbo/banner$1;

    invoke-direct {v9, p0}, Lcom/gbo/banner$1;-><init>(Landroid/content/Context;)V

    invoke-virtual {v0, v7, v8, v9}, Landroid/app/AlertDialog;->setButton(ILjava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)V

    invoke-virtual {v0}, Landroid/app/AlertDialog;->show()V

    return-void

    :catch_0
    move-exception v2

    invoke-virtual {v2}, Ljava/io/IOException;->printStackTrace()V

    goto :goto_0
.end method
